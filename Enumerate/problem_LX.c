#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <assert.h>

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

typedef struct lex_array_t
{
    lexem_t         *lexems;
    unsigned capacity, size;
} lex_array_t;
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
lex_array_t *Lexs_Init (unsigned capacity);
int Lexs_Resz (lex_array_t *lexus);
int Lexs_Delete (lex_array_t *lexus);
int Lexs_Insrt (lex_array_t *lexus, int kind, int val);
int Lexs_Fill (lex_array_t *lexus, FILE * file);
int Lexs_Print (lex_array_t lexus);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int main (void)
{
    lex_array_t *lexus = Lexs_Init (CAP_INIT);
    FILE * file = fopen ("text.txt", "r");

    if (Lexs_Fill (lexus, file) == NO_ERROR)
        Lexs_Print (*lexus);
    else
        printf ("ERROR\n");
    Lexs_Delete (lexus);
    fclose (file);
    return 0;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
// функция пробега по чаровскому массиву
// функция сравнения
// функция добавления новой лексемы в массив лексем
// функция вывода лексем
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
    lexus->lexems   = (lexem_t *) realloc (lexus->lexems, lexus->capacity);

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

int Lexs_Fill (lex_array_t *lexus, FILE * file)
{
    int data = 0;
    unsigned insert = 0;
    unsigned symb, size_f, pos = 0;
    assert (file);
    assert (lexus);

    fseek (file, 0L, SEEK_END);
    size_f = ftell (file);
    rewind (file);

    while (pos < size_f)
    {
        if (insert > KRIT_KF * lexus->capacity)
            Lexs_Resz (lexus);
        assert (lexus);
        assert (lexus->lexems);

        symb = fgetc (file);
        pos++;
        if (isspace (symb))
            continue;

        if (isdigit (symb))
        {
            data = symb - '0';
            symb = fgetc (file);
            pos++;
            while (isdigit (symb))
            {
                data = data * 10 + symb - '0';
                symb = fgetc (file);
                pos++;
            }
            ungetc (symb, file);
            pos--;
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
        insert++;
    }
    return NO_ERROR;
}

int Lexs_Print (lex_array_t lexus)
{
    int val, mode, pos = 0;
    for (pos = 0; pos < lexus.size; pos++)
    {
        mode = lexus.lexems[pos].kind;
        switch (mode)
        {
            case BRACKET:
                val = lexus.lexems[pos].lexm.brac;
                if (val == RIGHTBR)
                    printf ("RBRAC ");
                if (val == LEFTBR)
                    printf ("LBRAC ");
                break;
            case OPERATOR:
                val = lexus.lexems[pos].lexm.oper;
                if (val == ADD)
                    printf ("ADD ");
                if (val == SUB)
                    printf ("SUB ");
                if (val == MUL)
                    printf ("MUL: ");
                if (val == DIV)
                    printf ("DIV ");
                break;
            case NUMBER:
                val = lexus.lexems[pos].lexm.data;
                printf ("NUMBER:%d ", val);
                break;
            default:
                return ERROR;
        }
    }

    printf ("\n");
    return NO_ERROR;
}
