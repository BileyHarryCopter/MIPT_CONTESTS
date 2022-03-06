#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum ways
{
    LEFT = 1,
    RIGHT
};

typedef struct node_t
{
    struct node_t  *next;
    int             data;
} node_t;

typedef struct tree
{
    struct tree  *right;
    struct tree   *left;
    int            data;
} BinTree;

int Tree_Print (BinTree *top);
int *data_fill (int *buff, int size, int mode);

void Tree_Ctor (BinTree * top, int top_data);
void Tree_Insert (BinTree *knot, int way, int knot_data);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int main (void)
{
    BinTree * tree = (BinTree *) calloc (1, sizeof (BinTree));

    Tree_Ctor (tree, 4);
    Tree_Insert (tree, LEFT, 3);
    Tree_Insert (tree, RIGHT, 0);
    Tree_Insert (tree->left, LEFT, 1);
    Tree_Insert (tree->right, LEFT, 2);


    Tree_Print (tree);
    printf ("\n");
    return 0;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
void Tree_Ctor (BinTree *top, int top_data)
{
    top->right = (BinTree *) calloc (1, sizeof (BinTree));
    top->left  = (BinTree *) calloc (1, sizeof (BinTree));
    top->data = top_data;
}

void Tree_Insert (BinTree *knot, int way, int knot_data)
{
    if (way == LEFT)
    {
        knot->left        = (BinTree *) calloc (1, sizeof (BinTree));
        knot->left->data  = knot_data;
    }
    if (way == RIGHT)
    {
        knot->right       = (BinTree *) calloc (1, sizeof (BinTree));
        knot->right->data = knot_data;
    }
}

int Tree_Print (BinTree *top)
{
    printf ("%d ", top->data);
    if (!top->left && !top->right)
        return 0;
    else if (!top->left && top->right)
        return Tree_Print (top->right);
    else if (!top->right && top->left)
        return Tree_Print (top->left);
    else if (Tree_Print (top->left) == 0)
        return Tree_Print (top->right);
}

int Tree_Rec ()

//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
