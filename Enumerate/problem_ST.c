#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#define KRIT_KF 0.6
#define ENCR_KF 2

enum mode_node
{
    FALSE = 0,
    TRUE,
    LEFT,
    RIGHT
};
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
            //  for array of lexems //
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
typedef int data_t;

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
    DIV,
    ADD_SUB,
    MUL_DIV
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
    data_t             data;
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

typedef struct lexer_state
{
    lex_array_t      lexarr;
    int             current;
} lexer_state;

typedef struct node_t
{
    struct node_t    *right;
    struct node_t     *left;
    lexem_t       node_data;
} node_t;
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
                //      functions for working with tree       //
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int Tree_Delete (node_t *top);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
                //      functions for creating lex_arr       //
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
lex_array_t *Lexs_Init (unsigned capacity);
int Lexs_Resz (lex_array_t *lexus);
int Lexs_Delete (lex_array_t *lexus);
int Lexs_Insrt (lex_array_t *lexus, int kind, int val);
int Lexs_Fill (lex_array_t *lexus);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
                //      functions for parcing the lex_arr    //
//===*=======*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
lexem_t *Cur_St (lexer_state *state);

int Dump_Tree (node_t *top);
int IS (lexer_state *lex_state, int mode);

node_t *Parce_Expr (lexer_state *state);
node_t *Parce_Mult (lexer_state *state);
node_t *Parce_Term (lexer_state *state);
node_t *Build_Syntax_Tree (lex_array_t lexus_ar);

data_t Calc_Result (node_t *top);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int main (void)
{
    node_t *tree = NULL;
    lex_array_t *lexus = Lexs_Init (CAP_INIT);
    if (Lexs_Fill (lexus) == NO_ERROR)
    {
        tree = Build_Syntax_Tree (*lexus);
    }
    else
        printf ("ERROR\n");
	return 0;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int Tree_Delete (node_t *top)
{
    if (!top->left && !top->right)
    {
        free (top);
        top->node_data.lexm.data = 0;
        return NO_ERROR;
    }
    if (top->left && !top->right)
        return Tree_Delete (top->left);
    if (!top->left && top->right)
        return Tree_Delete (top->right);
    if (top->left && top->right && Tree_Delete (top->left) == NO_ERROR)
        return Tree_Delete (top->right);

    return ERROR;
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
lexem_t *Cur_St (lexer_state *state)
{
    assert (state);
    return (state->lexarr.lexems + state->current);
}

int IS (lexer_state *lex_state, int mode)
{
    assert (lex_state);
    lexem_t *state = Cur_St (lex_state);
    switch (mode)
    {
        case ADD_SUB:
            if (state->kind == OPERATOR && (state->lexm.oper == ADD || state->lexm.oper == SUB))
                return TRUE;
        case ADD:
            if (state->kind == OPERATOR && state->lexm.oper == ADD)
                return TRUE;
        case MUL_DIV:
            if (state->kind == OPERATOR && (state->lexm.oper == MUL || state->lexm.oper == DIV))
                return TRUE;
        case MUL:
            if (state->kind == OPERATOR && state->lexm.oper == MUL)
                return TRUE;
        case LBRAC:
            if (state->kind == BRACKET && state->lexm.brac == LEFTBR)
                return TRUE;
        case RBRAC:
            if (state->kind == BRACKET && state->lexm.brac == RIGHTBR)
                return TRUE;
        case NUMBER:
            if (state->kind == NUMBER)
                return TRUE;
        default:
            return ERROR;
    }
    return ERROR;
}

node_t *Parce_Expr (lexer_state *state)
{
    node_t *right_part = NULL;
    node_t *left_part  = Parce_Mult (state);
    if (IS (state, ADD_SUB))
    {
        operator_t oper = SUB;
        if (IS (state, ADD))
            oper = ADD;
        state->current++;
        right_part = Parce_Expr (state);
        if (right_part == NULL)
        {
            //  TODO: normal correcting errors
            exit (EXIT_FAILURE);
        }
        node_t *expr = (node_t *) calloc (1, sizeof (node_t));
        expr->left   = left_part;
        expr->right  = right_part;
        expr->node_data.kind = OPERATOR;
        expr->node_data.lexm.oper = oper;
        return expr;
    }
    return left_part;
}

node_t *Parce_Mult (lexer_state *state)
{
    node_t *right_part = NULL;
    node_t *left_part  = Parce_Term (state);
    if (IS (state, MUL_DIV))
    {
        operator_t oper = DIV;
        if (IS (state, MUL))
            oper = MUL;
        state->current++;
        right_part = Parce_Mult (state);
        if (right_part == NULL)
        {
            //  TODO: normal correcting errors
            exit (EXIT_FAILURE);
        }
        node_t *mult = (node_t *) calloc (1, sizeof (node_t));
        mult->left   = left_part;
        mult->right  = right_part;
        mult->node_data.kind = OPERATOR;
        mult->node_data.lexm.oper = oper;
        return mult;
    }
    return left_part;
}

node_t *Parce_Term (lexer_state *state)
{
    if (IS (state, LBRAC))
    {
        node_t *expr = NULL;
        state->current++;
        expr = Parce_Expr (state);
        if (!IS (state, RBRAC))
        {
            //  TODO: normal correcting errors
            exit (EXIT_FAILURE);
        }
        return expr;
    }
    if (IS (state, NUMBER))
    {
        node_t *term = (node_t *) calloc (1, sizeof (node_t));
        term->node_data.lexm.data  = Cur_St (state)->lexm.data;
        return term;
    }
}

//  building a tree by array of lexems
node_t *Build_Syntax_Tree (lex_array_t lexus_ar)
{
    assert (lexus_ar.lexems);
    int current = 0;
    lexer_state state = {lexus_ar, current};
    return Parce_Expr (&state);
}

//  calculatung the result by tree's way out
data_t Calc_Result (node_t *top)
{
    assert (top);
    return 0;
}

//  normal Dump of the tree
int Dump_Tree (node_t *top)
{
    return 0;
}
