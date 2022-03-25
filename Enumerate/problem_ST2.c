#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

#define KRIT_KF 0.6
#define ENCR_KF 2

enum size
{
    CAP_INIT = 100
};

typedef enum lexem_kind_t {NO_ERROR = 0, OPERATOR, BRACKET, NUMBER, ERROR} lexem_kind_t;

typedef enum operator_t   {ADD      = 10, SUB, MUL, DIV}                     operator_t;

typedef enum bracket_t    {LEFTBR   = 20, RIGHTBR}                            bracket_t;

typedef enum node_kind_t  {NODE_VAL = 30, NODE_OPER}                        node_kind_t;

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

typedef struct lex_state
{
    lex_array_t      *lexus;
    unsigned        current;
} lex_state;

typedef union node_data_t
{
    operator_t        noper;
    int                data;
} node_data_t;

typedef struct node_t
{
    struct node_t *left, *right;
    node_data_t           ndata;
} node_t;
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
lex_array_t *Lexs_Init (unsigned capacity);
int Lexs_Resz (lex_array_t *lexus);
int Lexs_Delete (lex_array_t *lexus);
int Lexs_Insrt (lex_array_t *lexus, int kind, int val);
int Lexs_Fill (lex_array_t *lexus);
int Lexs_Print (lex_array_t lexus);

int Tree_Calculate (node_t *top);
node_t * Build_Syntax_Tree (lex_array_t *lexus);
node_t * Parce_Expr (lex_state * state);
node_t * Parce_Mult (lex_state * state);
node_t * Parce_Term (lex_state * state);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int main (void)
{
    node_t *tree = NULL;
    lex_array_t *lexus = Lexs_Init (CAP_INIT);
    if (Lexs_Fill (lexus) == NO_ERROR)
    {
        Lexs_Print (*lexus);
        tree = Build_Syntax_Tree (lexus);
        if (tree == NULL)
        {
            printf ("ERROR CRINGE\n");
            return 0;
        }
        printf ("%d\n", Tree_Calculate (tree));
    }
    else
        printf ("ERROR\n");
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
                    printf ("PLUS ");
                if (val == SUB)
                    printf ("MINUS ");
                if (val == MUL)
                    printf ("MUL ");
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
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int Tree_Calculate (node_t *top)
{
    int value_l  = 0;
    int value_r  = 0;
    int operator = 0;
    assert (top);
    if (!top->left && !top->right)
    {
        value_l = top->ndata.data;
        free (top);
        return value_l;
    }
    if (top->left && top->right)
    {
        value_l  = Tree_Calculate (top->left);
        value_r  = Tree_Calculate (top->right);
        operator = top->ndata.noper;

        top->left  = NULL;
        top->right = NULL;

        switch (operator)
        {
            case ADD:
                top->ndata.data = value_l + value_r;
                break;
            case SUB:
                top->ndata.data = value_l - value_r;
                break;
            case MUL:
                top->ndata.data = value_l * value_r;
                break;
            case DIV:
                top->ndata.data = value_l / value_r;
                break;
            default:
                printf ("LOOK AT THIS IN %s\n", __PRETTY_FUNCTION__);
                return ERROR;
        }
        return top->ndata.data;
    }

    printf ("LOOK AT THIS IN %s\n", __PRETTY_FUNCTION__);
    return ERROR;
}

node_t * Build_Syntax_Tree (lex_array_t *lexus)
{
    node_t *top = calloc (1, sizeof (node_t));
    assert (lexus);
    lex_state state = {lexus, 0};

    top = Parce_Expr (&state);

    return (top != NULL ) ? top : NULL;
}

node_t * Parce_Expr (lex_state * state)
{
    assert (state);
    int operator = 0;
    node_t *lbranch = Parce_Mult (state);

    if (state->lexus->lexems[state->current].kind == OPERATOR &&
    (state->lexus->lexems[state->current].lexm.oper == ADD || state->lexus->lexems[state->current].lexm.oper == SUB))
    {
        operator = state->lexus->lexems[state->current].lexm.oper;
        state->current++;
        node_t *rbranch = Parce_Expr (state);

        if (rbranch == NULL)
        {
            printf ("POPANDOS\n");
            return NULL;
        }

        node_t *cbranch = (node_t *) calloc (1, sizeof(node_t));
        cbranch->ndata.noper = operator;
        cbranch->left        = lbranch;
        cbranch->right       = rbranch;
        return cbranch;
    }

    return lbranch;
}

node_t * Parce_Mult (lex_state * state)
{
    assert (state);
    int operator = 0;
    node_t *lbranch = Parce_Term (state);

    if (state->lexus->lexems[state->current].kind == OPERATOR &&
    (state->lexus->lexems[state->current].lexm.oper == ADD || state->lexus->lexems[state->current].lexm.oper == SUB))
    {
        operator = state->lexus->lexems[state->current].lexm.oper;
        state->current++;
        node_t *rbranch = Parce_Mult (state);

        if (rbranch == NULL)
        {
            printf ("POPANDOS\n");
            return NULL;
        }

        node_t *cbranch = (node_t *) calloc (1, sizeof(node_t));
        cbranch->ndata.noper = operator;
        cbranch->left        = lbranch;
        cbranch->right       = rbranch;
        return cbranch;
    }

    return lbranch;
}

node_t * Parce_Term (lex_state * state)
{
    assert (state);
    node_t *tbranch = NULL;
    if (state->lexus->lexems[state->current].kind == BRACKET && state->lexus->lexems[state->current].lexm.brac == LEFTBR)
    {
        state->current++;
        tbranch = Parce_Expr (state);

        if (state->lexus->lexems[state->current].lexm.brac != RIGHTBR)
        {
            printf ("POPANDOS\n");
            return NULL;
        }
        return tbranch;
    }
    else if (state->lexus->lexems[state->current].kind == NUMBER)
    {
        tbranch = (node_t *) calloc (1, sizeof (node_t));
        tbranch->ndata.data = state->lexus->lexems[state->current].lexm.data;
        tbranch->left       = NULL;
        tbranch->right      = NULL;
        return tbranch;
    }

    printf ("LOOK AT THE %s\n", __PRETTY_FUNCTION__);
    return NULL;
}
