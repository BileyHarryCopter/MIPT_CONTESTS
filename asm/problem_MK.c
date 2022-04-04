#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define NDEBUG
#include <assert.h>
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//    initialisation of enums for lexems    //
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
#define KRIT_KF 0.6
#define ENCR_KF 2
#define CAP_INIT 10
#define STRSIZE 10
#define FILLBITE 256

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
lex_array_t *LexsInit (unsigned capacity);
int LexsResz (lex_array_t *lexus);
int LexsPrint (lex_array_t *lexus);
int LexsDelete (lex_array_t *lexus);
int LexsFill (lex_array_t *lexus, char * file_name);
int LexsInsrt (lex_array_t *lexus, int kind, int val);

int BinCtor (FILE * file, int first);
int RunProgram (lex_array_t * lexus);
int BinToLex (lex_array_t * lexus, int machine_word);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int main (int argc, char *argv[])
{
    lex_array_t *lexus = LexsInit (CAP_INIT);

//  обращение к файлу

    if (LexsFill (lexus, argv[argc - 1]) == NO_ERROR)
    {
        if (RunProgram (lexus) == ERROR)
        {
            printf ("ERROR\n");
            return ERROR;
        }
    }
    else
        printf ("ERROR\n");

    LexsDelete (lexus);
    return 0;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//  adding a lexic analyze  //
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int

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
                if (val == MOVI)
                    printf ("%s ", op_name[val]);
                else
                    printf ("%s ", op_name[val - ADD + 1]);
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
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int LexsFill (lex_array_t *lexus, char * file_name)
{
    int  val         = 0;
    char symb        = 0;
    FILE * buffer    = NULL;

    assert (lexus);
    buffer = fopen (file_name, "r");
    assert (buffer);
    fseek (buffer, 0L, SEEK_SET);

    while (symb != '\n')
    {
        if (lexus->size > KRIT_KF * lexus->capacity)
            LexsResz (lexus);
        assert (lexus);
        assert (lexus->lexems);

        symb = getc (buffer);

        if (isspace (symb) || symb == '\n')
            continue;

        if (symb == '0')
        {
            symb = getc (buffer);
            if (symb != 'x' && symb != 'X')
            {
                printf ("ERROR\n");
                return ERROR;
            }
            symb = getc (buffer);
            val  = BinCtor (buffer, symb);
            //printf ("%#x\n", val);
            if (BinToLex (lexus, val) == ERROR)
                return ERROR;
        }
    }

    fclose (buffer);
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

int BinToLex (lex_array_t * lexus, int machine_word)
{
    int val  = 0;
    int oper = 0;
    int op_flag = BINAR;

//  inserting of op_comand
    if (!(machine_word >> 7))
    {
//  inserting MOVI
        if (LexsInsrt (lexus, OPERATOR, MOVI) == ERROR)
            return ERROR;
        val = machine_word;
        if (LexsInsrt (lexus, CONSTANT, val) == ERROR)
            return ERROR;
    }
    else
    {
//  inserting command
        oper |= machine_word >> 4;
        switch (oper)
        {
//  inserting binar command
            case ADD_MASK >> 4:
                if (LexsInsrt (lexus, OPERATOR, ADD) == ERROR)
                    return ERROR;
                break;
            case SUB_MASK >> 4:
                if (LexsInsrt (lexus, OPERATOR, SUB) == ERROR)
                    return ERROR;
                break;
            case MUL_MASK >> 4:
                if (LexsInsrt (lexus, OPERATOR, MUL) == ERROR)
                    return ERROR;
                break;
            case DIV_MASK >> 4:
                if (LexsInsrt (lexus, OPERATOR, DIV) == ERROR)
                    return ERROR;
                break;
            case IN_MASK  >> 4:
//  nothing to insert because of future cheking  //
                op_flag = UNAR;
                break;
            default:
                return ERROR;
        }
        if (op_flag == UNAR)
        {
//  inserting unar command
            oper = machine_word >> 2;
            switch (oper)
            {
                case IN_MASK >> 2:
                    if (LexsInsrt (lexus, OPERATOR, IN) == ERROR)
                        return ERROR;
                    break;
                case OUT_MASK >> 2:
//  printf ("OUT IS HERE\n");
                    if (LexsInsrt (lexus, OPERATOR, OUT) == ERROR)
                        return ERROR;
                    break;
                default:
                    return ERROR;
            }
        }
//  inserting arguments of command
        val = machine_word;
        if (op_flag == UNAR)
        {
            switch (val & UNAR_MASK)
            {
                case A_MASK:
                    if (LexsInsrt (lexus, REGISTR, A) == ERROR)
                        return ERROR;
                    break;
                case B_MASK:
                    if (LexsInsrt (lexus, REGISTR, B) == ERROR)
                        return ERROR;
                    break;
                case C_MASK:
                    if (LexsInsrt (lexus, REGISTR, C) == ERROR)
                        return ERROR;
                    break;
                case D_MASK:
                    if (LexsInsrt (lexus, REGISTR, D) == ERROR)
                        return ERROR;
                    break;
                default:
                    return ERROR;
            }
        }
        else if (op_flag == BINAR)
        {
            val &= BINAR_MASK;
            switch (val >> 2)
            {
                case A_MASK:
                    if (LexsInsrt (lexus, REGISTR, A) == ERROR)
                        return ERROR;
                    break;
                case B_MASK:
                    if (LexsInsrt (lexus, REGISTR, B) == ERROR)
                        return ERROR;
                    break;
                case C_MASK:
                    if (LexsInsrt (lexus, REGISTR, C) == ERROR)
                        return ERROR;
                    break;
                case D_MASK:
                    if (LexsInsrt (lexus, REGISTR, D) == ERROR)
                        return ERROR;
                    break;
                default:
                    return ERROR;
            }
            val = machine_word;
            val &= UNAR_MASK;
            switch (val)
            {
                case A_MASK:
                    if (LexsInsrt (lexus, REGISTR, A) == ERROR)
                        return ERROR;
                    break;
                case B_MASK:
                    if (LexsInsrt (lexus, REGISTR, B) == ERROR)
                        return ERROR;
                    break;
                case C_MASK:
                    if (LexsInsrt (lexus, REGISTR, C) == ERROR)
                        return ERROR;
                    break;
                case D_MASK:
                    if (LexsInsrt (lexus, REGISTR, D) == ERROR)
                        return ERROR;
                    break;
                default:
                    return ERROR;
            }
        }
        else
            return ERROR;
    }

    return NO_ERROR;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int RunProgram (lex_array_t * lexus)
{
    unsigned oper, regr, first, second, data, pos = 0;
    int regrs [RLAST] = {0};
    assert (lexus);
    assert (lexus->lexems);

    while (pos != lexus->size)
    {
        oper = lexus->lexems[pos].lexm.oper;
        pos++;
        switch (oper)
        {
            case MOVI:
                if (lexus->lexems[pos].kind != CONSTANT)
                    return ERROR;
                data = lexus->lexems[pos].lexm.data;
                regrs[D] = data;
                break;

            case ADD:
                if (lexus->lexems[pos].kind != REGISTR)
                    return ERROR;
                regr   = lexus->lexems[pos].lexm.regr;
                first  = regrs[regr];
                pos++;
                if (lexus->lexems[pos].kind != REGISTR)
                    return ERROR;
                second = regrs[lexus->lexems[pos].lexm.regr];
                regrs[regr] = (first + second) % FILLBITE;
                break;
            case SUB:
                if (lexus->lexems[pos].kind != REGISTR)
                    return ERROR;
                regr   = lexus->lexems[pos].lexm.regr;
                first  = regrs[regr];
                pos++;
                if (lexus->lexems[pos].kind != REGISTR)
                    return ERROR;
                second = regrs[lexus->lexems[pos].lexm.regr];
                regrs[regr] = (first - second) % FILLBITE;
                break;
            case MUL:
                if (lexus->lexems[pos].kind != REGISTR)
                    return ERROR;
                regr   = lexus->lexems[pos].lexm.regr;
                first  = regrs[regr];
                pos++;
                if (lexus->lexems[pos].kind != REGISTR)
                    return ERROR;
                second = regrs[lexus->lexems[pos].lexm.regr];
                regrs[regr] = (first * second) % FILLBITE;
                break;
            case DIV:
                if (lexus->lexems[pos].kind != REGISTR)
                    return ERROR;
                regr   = lexus->lexems[pos].lexm.regr;
                first  = regrs[regr];
                pos++;
                if (lexus->lexems[pos].kind != REGISTR)
                    return ERROR;
                second = regrs[lexus->lexems[pos].lexm.regr];
                regrs[regr] = (first / second) % FILLBITE;
                break;
            case IN:
                if (lexus->lexems[pos].kind != REGISTR)
                    return ERROR;
                regr = lexus->lexems[pos].lexm.regr;
                fscanf (stdin, "%d", &regrs[regr]);
                break;
            case OUT:
                if (lexus->lexems[pos].kind != REGISTR)
                    return ERROR;
                regr = lexus->lexems[pos].lexm.regr;
                printf ("%d ", regrs[regr]);
                break;
            default:
                return ERROR;
        }
        pos++;
    }

    printf ("\n");
    return NO_ERROR;
}
