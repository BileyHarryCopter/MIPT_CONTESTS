#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>


enum ways
{
    LEFT = 1,
    RIGHT
};

enum mode
{
    NO_ERROR = 0,
    PRE,
    IN
};

typedef int data_t;

typedef struct tree
{
    struct tree  *right;
    struct tree   *left;
    data_t         data;
} bintree_t;


data_t * Buff_Ctor (FILE * file);
data_t * Mass_Fill (data_t *buffer, int mode);
int Mass_Print (data_t * array, unsigned size);
int Mass_Free (data_t * buffer);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int main (void)
{
    int *preorder, *inorder, *topology, *buffer = NULL;
    buffer = Buff_Ctor (stdin);
    assert (buffer);

    preorder = Mass_Fill (buffer, PRE);
    inorder  = Mass_Fill (buffer, IN);
    assert (preorder && inorder);

    Mass_Print (preorder, buffer[0]);
    Mass_Print (inorder, buffer[0]);
    Mass_Print (buffer, 2*buffer[0] + 1);

    Mass_Free (buffer);
    Mass_Free (preorder);
    Mass_Free (inorder);
    return 0;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
data_t * Buff_Ctor (FILE * file)
{
    unsigned nsymbs, pos = 0;
    data_t * buffer = NULL;
    scanf ("%d", &nsymbs);
    buffer = (int *) calloc (2*nsymbs + 1, sizeof (int));
    buffer[0] = nsymbs;
    for (pos = 1; pos < 2*nsymbs + 1; pos++)
    {
        scanf ("%d", buffer + pos);
    }
    return buffer;
}

data_t * Mass_Fill (data_t *buffer, int mode)
{
    unsigned nsymbs, pos = 0;
    data_t * array = NULL;
    assert (buffer);

    nsymbs = buffer[0];
    array  = (data_t *) calloc (nsymbs, sizeof(data_t));
    if (mode == PRE)
    {
        for (pos = 1; pos < nsymbs + 1; pos++)
        {
            array[pos - 1] = buffer[pos];
        }
    }
    else if (mode == IN)
    {
        for (pos = 1 + nsymbs; pos < 2*nsymbs + 1; pos++)
        {
            array[pos - nsymbs - 1] = buffer[pos];
        }
    }

    return array;
}

int Mass_Print (data_t * array, unsigned size)
{
    unsigned pos = 0;
    for (pos = 0; pos < size; pos++)
    {
        printf ("%d ", array[pos]);
    }
    printf ("\n");

    return NO_ERROR;
}

int Mass_Free (data_t * buffer)
{
    assert (buffer);
    free (buffer);

    return NO_ERROR;
}
/*
int * Topology_Ctor (FILE *file, int *preorder, int *inorder)
{
    unsigned nsymbs, pos = 0;
    bintree_t *tree = (bintree_t *) calloc (1, sizeof (bintree_t));

    scanf ("%d", &nsymbs);

    preorder = (int *) calloc (nsymbs, sizeof (int));
    inorder  = (int *) calloc (nsymbs, sizeof (int));

    for (pos = 0; pos < nsymbs; pos++)
    {
        scanf ("%d", preorder + pos);
    }
    for (pos = 0; pos < nsymbs; pos++)
    {
        scanf ("%d", inorder + pos);
    }

    tree = Tree_Ctor ();

    return tree;
}

void Tree_Ctor (bintree_t *top, int top_data)
{
    top->right = (bintree_t *) calloc (1, sizeof (bintree_t));
    top->left  = (bintree_t *) calloc (1, sizeof (bintree_t));
    top->data = top_data;
}

void Tree_Insert (bintree_t *knot, int way, int knot_data)
{
    if (way == LEFT)
    {
        knot->left        = (bintree_t *) calloc (1, sizeof (bintree_t));
        knot->left->data  = knot_data;
    }
    if (way == RIGHT)
    {
        knot->right       = (bintree_t *) calloc (1, sizeof (bintree_t));
        knot->right->data = knot_data;
    }
}

int Tree_Print (bintree_t *top)
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
*/
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
