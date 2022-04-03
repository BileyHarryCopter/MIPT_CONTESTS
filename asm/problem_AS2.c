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
    char val = 0;

    while (val != EOF)
    {
        scanf ("%#x", &val);
        printf ("val = %d\n", val);
    }

    return 0;
}
