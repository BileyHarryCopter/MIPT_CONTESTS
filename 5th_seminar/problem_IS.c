#include <stdio.h>
#include <stdlib.h>

struct tree_t {
  struct tree_t *left;
  struct tree_t *right;
  int data;
};
int check_is_bst (struct tree_t *top)
{
    if (!top->left && !top->right)
        return 1;
    else if (!top->left  && top->data < top->right->data)
        return check_is_bst (top->right);
    else if (!top->right && top->data > top->left->data)
        return check_is_bst (top->left);
    else if (top->left->data < top->data && check_is_bst (top->left) == 1)
    {
        if (top->right->data >= top->data)
        {
            top->data = top->right->data;
            if (top->data < top->left->data)
                return 0;
            return check_is_bst (top->right);
        }
        else
            return 0;
    }
    else
        return 0;
}
int main(void)
{
    return 0;
}
