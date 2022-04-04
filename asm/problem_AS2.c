#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//    initialisation of enums for lexems    //
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
enum errors
{
    NO_ERROR = 0,
    ERROR
};

enum op_flags
{
    UNAR = 1,
    BINAR = 2
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
#define UNAR_MASK 3     //
#define BINAR_MASK 12   //


#define MOVI_MASK 0     //
#define ADD_MASK  128   //      for
#define SUB_MASK  144   //          operators
#define MUL_MASK  160   //
#define DIV_MASK  176   //
#define IN_MASK   192   //
#define OUT_MASK  196   //
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//  function's definitions  //
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int RegrDtct (char regr);
int DataCtor (char first);
int OperDtct (char *oper);
char *OperCtor (char first);
int istrcmp (char * str1, const char * str2);


int ParceBin (int machine_word);
int ReadBinTransAsm (FILE * file);
int BinCtor (FILE * file, int first);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int main (void)
{
    ReadBinTransAsm (stdin);
    return 0;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int ReadBinTransAsm (FILE * file)
{
    int val = 0;
    while (val != EOF)
    {
        val = getc (file);
        if (isspace (val))
            continue;
        else if (val == '0')
        {
            val = getc (file);
            if (val != 'x' && val != 'X')
            {
                printf ("ERROR\n");
                return ERROR;
            }
            val = getc (file);
            val = BinCtor (file, val);
            ParceBin (val);
        }
    }

    return NO_ERROR;
}

int BinCtor (FILE * file, int first)
{
    int val  = 0;
    int symb = getc (file);

    if (isspace (symb))
    {
        if (first >= 'a' && first <= 'f')
            val += first - 'a' + 10;
        else if (isdigit (first))
            val += first - '0';
        else
            return -1;
        return val;
    }

    if (first >= 'a' && first <= 'f')
    {
        val += 16 * (first - 'a' + 10);
    }
    else if (isdigit (first))
        val += 16 * (first - '0');
    else
        return -1;

    if (symb >= 'a' && symb <= 'f')
        val += symb - 'a' + 10;
    else if (isdigit (symb))
        val += symb - '0';
    else
        return val;

    return val;
}

int ParceBin (int machine_word)
{
    int val  = 0;
    int oper = 0;
    int op_flag = BINAR;
    if (!(machine_word >> 7))
    {
        printf ("%s ", op_name[MOVI]);
        val = machine_word;
        printf ("%d\n", val);
    }
    else
    {
        oper |= machine_word >> 4;
        switch (oper)
        {
            case ADD_MASK >> 4:
                printf ("%s ", op_name[ADD - ADD + 1]);
                break;
            case SUB_MASK >> 4:
                printf ("%s ", op_name[SUB - ADD + 1]);
                break;
            case MUL_MASK >> 4:
                printf ("%s ", op_name[MUL - ADD + 1]);
                break;
            case DIV_MASK >> 4:
                printf ("%s ", op_name[DIV - ADD + 1]);
                break;
            case IN_MASK >> 4:
                //  nothing to write because of future cheking  //
                op_flag = UNAR;
                break;
            default:
                printf ("ERROR\n");
                return ERROR;
        }
        if (op_flag == UNAR)
        {
            //  work with IN / OUT command
            oper = machine_word >> 2;
            switch (oper)
            {
                case IN_MASK >> 2:
                    printf ("%s ", op_name[IN - ADD + 1]);
                    break;
                case OUT_MASK >> 2:
                    printf ("%s ", op_name[OUT - ADD + 1]);
                    break;
                default:
                    printf ("ERROR\n");
                    return ERROR;
            }
        }

        val = machine_word;
        if (op_flag == UNAR)
        {
            switch (val & UNAR_MASK)
            {
                case A_MASK:
                    printf ("A\n");
                    break;
                case B_MASK:
                    printf ("B\n");
                    break;
                case C_MASK:
                    printf ("C\n");
                    break;
                case D_MASK:
                    printf ("D\n");
                    break;
                default:
                    printf ("ERROR\n");
                    return ERROR;
            }
        }
        else if (op_flag == BINAR)
        {
            val &= BINAR_MASK;
            switch (val >> 2)
            {
                case A_MASK:
                    printf ("A, ");
                    break;
                case B_MASK:
                    printf ("B, ");
                    break;
                case C_MASK:
                    printf ("C, ");
                    break;
                case D_MASK:
                    printf ("D, ");
                    break;
                default:
                    printf ("ERROR\n");
                    return ERROR;
            }
            val = machine_word;
            val &= UNAR_MASK;
            switch (val)
            {
                case A_MASK:
                    printf ("A\n");
                    break;
                case B_MASK:
                    printf ("B\n");
                    break;
                case C_MASK:
                    printf ("C\n");
                    break;
                case D_MASK:
                    printf ("D\n");
                    break;
                default:
                    printf ("ERROR\n");
                    return ERROR;
            }
        }
        else
        {
            printf ("ERROR\n");
            return ERROR;
        }
    }

    return NO_ERROR;
}
