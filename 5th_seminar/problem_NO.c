#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct tree
{
    struct tree  *right;
    struct tree   *left;
    int            data;
} b_tree;

int Tree_Print (BinTree *top);

//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int main (void)
{
    int i = 0;
    b_tree tree = {};
    int n_knot = 0;
    scanf ("%d", &n_knot);
    int *data = (int *) calloc (n_knot, sizeof (int));

    for (i = 0; i < n_knot; i++)
        scanf ("%d", data + i);

    tree->data = data[0];

    for (i = 1; i < n_knot; i++)
    {
        Tree_Init (tree, data[i]);
    }

    return 0;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int Tree_Init (b_tree *top, int data)
{
    if (data > top->data)
    {
        
    }
    else if (data < top->)
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
