#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum paths {
    RIGHT = 1,
    LEFT
};

typedef struct list {
    struct list *next;
    int data;
} List;

typedef struct tree {
    struct tree *right;
    struct tree *left;
    int data;
} Tree;
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
                //  adding function for working with tree   //
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
void Knot_Init (Tree * knot, int data)
{
    knot        = (Tree *) calloc (1, sizeof (Tree));
    knot->data  = data;
    knot->right = NULL;
    knot->left  = NULL;
}
void Tree_Insert (Tree * knot, int data, int mode)
{
    if (mode == RIGHT)
    {
        Knot_Init (knot->right, data);
    }
    else if (mode == LEFT)
    {
        Knot_Init (knot->left, data);
    }
}
/*
int Preorder_in (Tree knot, int * mass)
{

}
void Inorder_in (Tree top, int * mass)
{

}
*/
void Tree_Out (Tree * top)
{
    List top_list = (List *) calloc (1, sizeof (List));
    top_list->next = top;
    top_list->next->next = NULL;
    top_list->data = top_tree->data;
    printf ("%d", top_list->data);

    while (top_list->next != NULL)
    {

    }
}
Tree * Tree_Delete (Tree * top)
{
    if (top->left != NULL)
        top->left = Tree_Delete (top->left);
    else if (top->right != NULL)
        top->right = Tree_Delete (top->right);
    else if (top -> left == NULL && top->right == NULL)
        return NULL;
}
int main (void)
{

    return 0;
}
