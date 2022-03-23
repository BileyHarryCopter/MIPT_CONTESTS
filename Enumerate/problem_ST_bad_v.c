#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <assert.h>
#include <math.h>

#define KRIT_KF 0.6
#define ENCR_KF 2

enum size
{
    CAP_INIT = 100
};

typedef enum lexem_kind_t
{
    NO_ERROR = 0,
    OPERATOR,
    BRACKET,
    NUMBER,
    ERROR
} lexem_kind_t;

typedef enum operator_t
{
    ADD = 10,
    SUB,
    MUL,
    DIV
} operator_t;

typedef enum bracket_t
{
    LEFTBR = 20,
    RIGHTBR
} bracket_t;

typedef union lexem
{
    operator_t         oper;
    bracket_t          brac;
    int                data;
} lexem;

typedef struct lexem_t
{
    lexem_kind_t       kind;
    lexem              lexm;
} lexem_t;

typedef struct lexem_array_t
{
    lexem_t         *lexems;
    unsigned capacity, size;
} lex_array_t;

//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
lex_array_t *Lexs_Init (unsigned capacity);
int Lexs_Resz (lex_array_t *lexus);
int Lexs_Fill (lex_array_t *lexus);
int Lexs_Delete (lex_array_t *lexus);
int Lexs_Insrt (lex_array_t *lexus, int kind, int val);

int Parce_Expr (lex_array_t *lexus);
int Parce_Mult (lex_array_t *lexus);
int Parce_Brac (lex_array_t *lexus);
int Parce_Lexem (lex_array_t *lexus);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int main (void)
{
    int ans = 0;
    lex_array_t *lexus = Lexs_Init (CAP_INIT);
    if (Lexs_Fill (lexus) == NO_ERROR)
    {
        lexus->capacity = lexus->size;
        lexus->size = 0;
        ans = Parce_Lexem (lexus);
        if (ans == ERROR)
        {
            printf ("ERROR\n");
            return 0;
        }
        printf ("%d\n", ans);
    }
    else
        printf ("ERROR\n");
    Lexs_Delete (lexus);
    return 0;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
lex_array_t *Lexs_Init (unsigned capacity)
{
    lex_array_t *lexus = (lex_array_t *) calloc (1, sizeof (lex_array_t));
    lexus->lexems   = (lexem_t *) calloc (capacity, sizeof (lexem_t));
    lexus->capacity = capacity;
    lexus->size     = 0;
    return lexus;
}

int Lexs_Resz (lex_array_t *lexus)
{
    assert (lexus);
    assert (lexus->lexems);
    lexus->capacity = ENCR_KF * lexus->capacity;
    lexus->lexems   = (lexem_t *) realloc (lexus->lexems, lexus->capacity * sizeof (lexem_t));
    return NO_ERROR;
}

int Lexs_Delete (lex_array_t *lexus)
{
    assert (lexus);
    assert (lexus->lexems);
    free   (lexus->lexems);
    free   (lexus);
    return NO_ERROR;
}

int Lexs_Insrt (lex_array_t *lexus, int kind, int val)
{
    int size = lexus->size;
    lexus->lexems[size].kind = kind;
    switch (kind)
    {
        case OPERATOR:
            lexus->lexems[size].lexm.oper = val;
            break;
        case BRACKET:
            lexus->lexems[size].lexm.brac = val;
            break;
        case NUMBER:
            lexus->lexems[size].lexm.data = val;
            break;
        default:
            return ERROR;
    }
    lexus->size++;

    return NO_ERROR;
}

int Lexs_Fill (lex_array_t *lexus)
{
    int data = 0;
    unsigned symb = 0;

    assert (lexus);

    while (symb != EOF)
    {
        if (lexus->size > KRIT_KF * lexus->capacity)
            Lexs_Resz (lexus);
        assert (lexus);
        assert (lexus->lexems);

        symb = getc (stdin);
        if (isspace (symb) || symb == EOF)
            continue;

        if (isdigit (symb))
        {
            data = symb - '0';
            symb = getc (stdin);
            while (isdigit (symb))
            {
                data = data * 10 + symb - '0';
                symb = getc (stdin);
            }
            ungetc (symb, stdin);
            Lexs_Insrt (lexus, NUMBER, data);
        }
        else
        {
            switch (symb)
            {
                case '(':
                    Lexs_Insrt (lexus, BRACKET, LEFTBR);
                    break;
                case ')':
                    Lexs_Insrt (lexus, BRACKET, RIGHTBR);
                    break;
                case '+':
                    Lexs_Insrt (lexus, OPERATOR, ADD);
                    break;
                case '-':
                    Lexs_Insrt (lexus, OPERATOR, SUB);
                    break;
                case '*':
                    Lexs_Insrt (lexus, OPERATOR, MUL);
                    break;
                case '/':
                    Lexs_Insrt (lexus, OPERATOR, DIV);
                    break;
                default:
                    return ERROR;
            }
        }
    }

    return NO_ERROR;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int Parce_Lexem (lex_array_t *lexus)
{
    int value = Parce_Expr (lexus);

    return value;
}

int Parce_Expr (lex_array_t *lexus)
{
    int value_1 = Parce_Mult (lexus);

    while (lexus->lexems[lexus->size].lexm.oper == ADD || lexus->lexems[lexus->size].lexm.oper == SUB)
    {
        int op = lexus->lexems[lexus->size].lexm.oper;

        lexus->size++;
        int value_2 = Parce_Mult (lexus);

        if (op == ADD)
            value_1 += value_2;
        else if (op == SUB)
            value_1 -= value_2;
    }
    return value_1;
}

int Parce_Mult (lex_array_t *lexus)
{
    int value_1 = Parce_Brac (lexus);

    while (lexus->lexems[lexus->size].lexm.oper == MUL || lexus->lexems[lexus->size].lexm.oper == DIV)
    {
        int op = lexus->lexems[lexus->size].lexm.oper;

        lexus->size++;
        int value_2 = Parce_Brac (lexus);

        if (op == MUL)
            value_1 *= value_2;
        else if (op == DIV)
            value_1 = (double) value_1 / value_2;
    }
    return value_1;
}

int Parce_Brac (lex_array_t *lexus)
{
    if (lexus->lexems[lexus->size].lexm.brac == LEFTBR)
    {
        lexus->size++;
        int value = Parce_Expr (lexus);
        if (lexus->lexems[lexus->size].lexm.brac != RIGHTBR)
            return ERROR;
        lexus->size++;
        return value;
    }
    else
        return lexus->lexems[lexus->size].lexm.data;
}
