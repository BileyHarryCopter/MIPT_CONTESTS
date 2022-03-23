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

typedef int data_t;
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
            //  for array of lexems //
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
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
    struct node_t  *right;
    struct node_t   *left;
    lexem_t     node_data;
} node_t;
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int Tree_Delete (node_t *top);
node_t * Tree_Ctor (data_t data);
int Tree_Add (node_t *parent, int mode, data_t data);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int main (void)
{
    node_t *top = Tree_Ctor (10);
    for (int i = 0; i < 100; i++)
    {
        Tree_Add (top, LEFT, 10 + i);
        top = top->left;
    }
    Tree_Delete (top);
	return 0;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
node_t * Tree_Ctor (data_t data)
{
    node_t *knot = (node_t *) calloc (1, sizeof (node_t));
    knot->left  = NULL;
    knot->right = NULL;
    knot->data  = data;
    return knot;
}

int Tree_Add (node_t *parent, int mode, data_t data)
{
    assert (parent);
    node_t *knot = (node_t *) calloc (1, sizeof (node_t));

    if (mode == LEFT)
        parent->left  = knot;
    else if (mode == RIGHT)
        parent->right = knot;
    else
        return ERROR;

    knot->left  = NULL;
    knot->right = NULL;

    return NO_ERROR;
}

int Tree_Delete (node_t *top)
{
    if (!top->left && !top->right)
    {
        free (top);
        top->data = 0;
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

lexem_t Cur_St (lexer_state *state)
{
    assert (state);
    return state->lexarr->lexems[state->current];
}

int Is_Add_Sub (lexem_t * lex_state)
{
    assert (lex_state);
    if (lex_state->kind == OPERATOR && (lex_state->lexm.oper == ADD || lex_state->lexm.oper == SUB))
        return TRUE;
    return FALSE;
}

int Is_Add (lexem_t * lex_state)
{
    assert (lex_state);
    if (lex_state->kind == OPERATOR && lex_state->lexm.oper == ADD)
        return TRUE;
    return FALSE;
}

int Is_Mul_Div (lexem_t * lex_state)
{
    assert (lex_state);
    if (lex_state->kind == OPERATOR && (lex_state->lexm.oper == MUL || lex_state->lexm.oper == DIV))
        return TRUE;
    return FALSE;
}

int Is_Mul (lexem_t * lex_state)
{
    assert (lex_state);
    if (lex_state->kind == OPERATOR && lex_state->lexm.oper == MUL)
        return TRUE;
    return FALSE;
}

int Is_LBrace (lexem_t * lex_state)
{
    assert (lex_state);
    if (lex_state->kind == BRACKET && lex_state->lexm.brac == LEFTBR)
        return TRUE;
    return FALSE;
}

int Is_RBrace (lexem_t * lex_state)
{
    assert (lex_state);
    if (lex_state->kind == BRACKET && lex_state->lexm.brac == RIGHTBR)
        return TRUE;
    return FALSE;
}

node_t *Parce_Expr (lexer_state *state)
{
    node_t *right_part = NULL;
    node_t *left_part  = Parce_Mult (state);
    if (Is_Add_Sub (state))
    {
        operator_t oper = SUB;
        if (Is_Add (state))
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
        expr->node_data.data.oper = oper;
        return expr;
    }
    return left_part;
}

node_t *Parce_Mult (lexer_state *state)
{
    node_t *right_part = NULL;
    node_t *left_part  = Parce_Term (state);
    if (Is_Mul_Div (state))
    {
        operator_t oper = DIV;
        if (Is_Mul (state))
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
        mult->node_data.data.oper = oper;
        return mult;
    }
    return left_part;
}

node_t *Parce_Term (lexer_state *state)
{
    if (Is_LBrace (state))
    {
        node_t *expr = NULL;
        state->current++;
        expr = Parce_Expr (state);
        if (!Is_RBrace (state))
        {
            //  TODO: normal correcting errors
            exit (EXIT_FAILURE);
        }
        return expr;
    }
    if (Is_Number (state))
    {
        node_t *term = (node_t *) calloc (1, sizeof (node_t));
        term->data  = Cur_St (state).lexm.data;
        return term;
    }
}

//  building a tree by array of lexems
node_t *Build_Syntax_Tree (lex_array_t lexus_ar)
{
    assert (&lexus_ar);
    int current = 0;
    lexer_state state = {lexus_ar, current};
    return Parce_Expr (&state);
}

//  calculatung the result by tree's way out
data_t Calc_Result (node_t *top)
{

}
