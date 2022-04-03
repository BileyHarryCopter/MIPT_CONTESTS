#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
                //    initialisation of enums for lexems    //
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
#define KRIT_KF 0.6
#define ENCR_KF 2
#define CAP_INIT 10
#define STRSIZE 10

enum errors
{
    NO_ERROR = 0,
    ERROR
};

typedef enum lexem_kind
{
    REGISTR = 0,
    OPERATOR,
    CONSTANT
}   lexem_kind;

typedef enum registers
{
    A = 0,
    B,
    C,
    D,
    RLAST
}   registers;

typedef enum operators
{
    MOVI = 0,
    ADD = 8,
    SUB,
    MUL,
    DIV,
    IN,
    OUT,
    OPLAST
}   operators;

static const char *op_name [OPLAST] =
{
    "MOVI",             //      arg = number
    "ADD",              //      2 args - 2 registrs
    "SUB",              //      2 args - 2 registrs
    "MUL",              //      2 args - 2 registrs
    "DIV",              //      2 args - 2 registrs
    "IN",               //      1 arg  - 1 registr
    "OUT",              //      1 arg  - 1 registr
    "OPLAST"            //      cringe moment
};
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
                            //  for bit fields  //
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
#define A_MASK 0        //
#define B_MASK 1        //      for
#define C_MASK 2        //          registrs
#define D_MASK 3        //

#define MOVI_MASK 0     //
#define ADD_MASK  128   //      for
#define SUB_MASK  144   //          operators
#define MUL_MASK  160   //
#define DIV_MASK  176   //
#define IN_MASK   192   //
#define OUT_MASK  196   //
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
typedef union lexem
{
    registers      regr;
    operators      oper;
    int            data;
}   lexem;

typedef struct lexem_t
{
    lexem_kind     kind;
    lexem          lexm;
}   lexem_t;

typedef struct lex_array_t
{
    lexem_t        *lexems;
    unsigned       capacity, size;
} lex_array_t;

//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
                        //  function's definitions  //
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int RegrDtct (char regr);
int DataCtor (char first);
int OperDtct (char *oper);
char *OperCtor (char first);
int LexsResz (lex_array_t *lexus);
int LexsFill (lex_array_t *lexus);
int LexsPrint (lex_array_t *lexus);
int LexsDelete (lex_array_t *lexus);
int LexsPrintBin (lex_array_t * lexus);
lex_array_t *LexsInit (unsigned capacity);
int istrcmp (char * str1, const char * str2);
int LexsInsrt (lex_array_t *lexus, int kind, int val);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int main (void)
{
    lex_array_t *lexus = LexsInit (CAP_INIT);
    if (LexsFill (lexus) == NO_ERROR)
    {
        //  LexsPrint (lexus);
        LexsPrintBin (lexus);
    }
    else
        printf ("You are fucking bastard!\n");

    LexsDelete (lexus);
    return 0;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
                        //  adding a lexic analyze  //
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
lex_array_t *LexsInit (unsigned capacity)
{
    lex_array_t *lexus = (lex_array_t *) calloc (1, sizeof (lex_array_t));
    lexus->lexems   = (lexem_t *) calloc (capacity, sizeof (lexem_t));
    lexus->capacity = capacity;
    lexus->size     = 0;
    return lexus;
}

int LexsResz (lex_array_t *lexus)
{
    assert (lexus);
    assert (lexus->lexems);
    lexus->capacity = ENCR_KF * lexus->capacity;
    lexus->lexems   = (lexem_t *) realloc (lexus->lexems, lexus->capacity * sizeof (lexem_t));
    return NO_ERROR;
}

int LexsDelete (lex_array_t *lexus)
{
    assert (lexus);
    assert (lexus->lexems);
    free   (lexus->lexems);
    free   (lexus);
    return NO_ERROR;
}

int LexsInsrt (lex_array_t *lexus, int kind, int val)
{
    int size = lexus->size;
    lexus->lexems[size].kind = kind;
    switch (kind)
    {
        case CONSTANT:
            lexus->lexems[size].lexm.data = val;
            break;
        case REGISTR:
            lexus->lexems[size].lexm.regr = val;
            break;
        case OPERATOR:
            lexus->lexems[size].lexm.oper = val;
            break;
        default:
            return ERROR;
    }
    lexus->size++;

    return NO_ERROR;
}

int LexsFill (lex_array_t *lexus)
{
    int oper        = 0;
    int data        = 0;
    char symb        = 0;
    char regr        = 0;
    char *oper_name = NULL;

    assert (lexus);

    while (symb != EOF)
    {
        if (lexus->size > KRIT_KF * lexus->capacity)
            LexsResz (lexus);
        assert (lexus);
        assert (lexus->lexems);

        symb = getc (stdin);

        if (isspace (symb) || symb == EOF)
            continue;

        if (isdigit (symb))
        {
            data = DataCtor (symb);
            LexsInsrt (lexus, CONSTANT, data);
        }
        else if (isalpha (symb))
        {
            //  for registr checking  //
            regr = symb;
            symb = getc (stdin);
            if (isspace (symb) || symb == ',')
            {
                regr = RegrDtct (regr);
                LexsInsrt (lexus, REGISTR, regr);
                continue;
            }
            ungetc (symb, stdin);
            symb = regr;
            //  for registr checking  //


            //   for operator checking   //
            oper_name   = OperCtor (symb);
            //printf ("operator: %s\n", oper_name);
            oper        = OperDtct (oper_name);
            LexsInsrt (lexus, OPERATOR, oper);
            free (oper_name);
            //   for operator checking   //
        }
    }

    return NO_ERROR;
}

int LexsPrint (lex_array_t *lexus)
{
    int val, kind = 0;
    unsigned pos = 0;
    for (pos = 0; pos < lexus->size; pos++)
    {
        kind = lexus->lexems[pos].kind;
        switch (kind)
        {
            case OPERATOR:
                val = lexus->lexems[pos].lexm.oper;
                printf ("%s ", op_name[val]);
                break;
            case REGISTR:
                val = lexus->lexems[pos].lexm.regr;
                if (val == A)
                    printf ("A ");
                else if (val == B)
                    printf ("B ");
                else if (val == C)
                    printf ("C ");
                else if (val == D)
                    printf ("D ");
                else
                    printf ("RLAST ");
                break;
            case CONSTANT:
                val = lexus->lexems[pos].lexm.data;
                printf ("%d ", val);
                break;
            default:
                return ERROR;
        }
    }

    printf ("\n");
    return NO_ERROR;
}

int LexsPrintBin (lex_array_t * lexus)
{
    int pos  = 0;
    int kind = 0;
    int oper = 0;
    int regr = 0;
    int val  = 0;

    for (pos = 0; pos < lexus->size; pos++)
    {
        kind = lexus->lexems[pos].kind;
        if (kind == OPERATOR)
        {
            val = 0;
            oper = lexus->lexems[pos].lexm.oper;
            //  printf ("\noperator = %s\n", op_name[oper]);
            switch (oper)
            {
                case 0:
                    val |= MOVI_MASK;
                    break;
                case 1:
                    val |= ADD_MASK;
                    break;
                case 2:
                    val |= SUB_MASK;
                    break;
                case 3:
                    val |= MUL_MASK;
                    break;
                case 4:
                    val |= DIV_MASK;
                    break;
                case 5:
                    val |= IN_MASK;
                    break;
                case 6:
                    val |= OUT_MASK;
                    break;
                default:
                    printf ("ERROR\n");
                    return ERROR;
            }
            pos++;
            switch (oper)
            {
                case 0:
                    if (lexus->lexems[pos].kind != CONSTANT)
                    {
                        printf ("ERROR\n");
                        return ERROR;
                    }
                    val = lexus->lexems[pos].lexm.data;
                    printf ("%#x ", val);
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                    if (lexus->lexems[pos].kind != REGISTR || lexus->lexems[pos].lexm.regr == RLAST)
                    {
                        printf ("ERROR\n");
                        return ERROR;
                    }
                    //  set the first reg
                    regr = lexus->lexems[pos].lexm.regr;
                    val = ((val >> 2) | regr) << 2;
                    //  set the second reg
                    pos++;
                    if (lexus->lexems[pos].kind != REGISTR || lexus->lexems[pos].lexm.regr == RLAST)
                    {
                        printf ("ERROR\n");
                        return ERROR;
                    }
                    regr = lexus->lexems[pos].lexm.regr;
                    val |= regr;
                    printf ("%#x ", val);
                    break;
                case 5:
                case 6:
                    if (lexus->lexems[pos].kind != REGISTR || lexus->lexems[pos].lexm.regr == RLAST)
                    {
                        printf ("ERROR\n");
                        return ERROR;
                    }
                    regr = lexus->lexems[pos].lexm.regr;
                    val |= regr;
                    printf ("%#x ", val);
                    break;
                default:
                    printf ("ERROR\n");
                    return ERROR;
            }
        }
        else
        {
            printf ("ERROR");
            return ERROR;
        }
    }
    return NO_ERROR;
}

char * OperCtor (char first)
{
    unsigned pos = 0;
    char *oper   = calloc (STRSIZE, sizeof (char));
    *oper        = first;
    first        = getc(stdin);
    pos          = 1;
    while (isalpha (first))
    {
        *(oper + pos) = first;
        first = getc (stdin);
        pos++;
    }
    ungetc (first, stdin);

    return oper;
}

int DataCtor (char first)
{
    int data = first - '0';
    first = getc (stdin);
    while (isdigit (first))
    {
        data = data * 10 + first - '0';
        first = getc (stdin);
    }
    ungetc (first, stdin);

    return data;
};

int OperDtct (char *oper)
{
    int i = 0;
    assert (oper);

    if (istrcmp (oper, op_name[i]) == 0)
    {
        //  printf ("%d - %s\n", MOVI, op_name[MOVI]);
        return MOVI;
    }

    for (i = ADD; i < OPLAST; i++)
    {
        if (istrcmp (oper, op_name[i - ADD + 1]) == 0)
        {
            //  printf ("%d - %s\n", i - ADD + 1, op_name[i - ADD + 1]);
            return i - ADD + 1;
        }
    }

    return OPLAST;
}

int RegrDtct (char regr)
{
    switch (regr)
    {
        case 'A':
            return A;
        case 'B':
            return B;
        case 'C':
            return C;
        case 'D':
            return D;
        default:
            return RLAST;
    }
}

int istrcmp (char * str1, const char * str2)
{
    while (isalpha (*str1) != 0)
    {
        if (tolower (*str1) != tolower (*str2))
        {
            return (*str1 - *str2);
        }
        str1++;
        str2++;
    }
    return (*str1 == ' ' || *str1 == '\t' || *str1 == '\n' || *str1 == '\0') ? 0 : -1;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
