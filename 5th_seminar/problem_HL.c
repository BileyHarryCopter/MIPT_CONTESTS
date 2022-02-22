#include <stdio.h>
#include <stdlib.h>

struct node_t {
    struct node_t *next;
    int data;
};

int If_pow2 (unsigned int numb)
{
    for (int i = 0; numb > 1; i++)
    {
        if (numb % 2 == 0)
            numb = numb / 2;
        else
            return 0;
    }
    return 1;
}

// определяет есть ли петля в односвязном списке
// возвращает 0 если нет и 1 если есть
int list_is_a_loop (struct node_t * top)
{
    unsigned int rbit    = 1;
    struct node_t * rbit_ptr;
    struct node_t * trtl_ptr = (struct node_t *) calloc (1, sizeof (struct node_t));

    rbit_ptr = top;

    while (rbit_ptr != NULL && rbit_ptr -> next != NULL)
    {
        if (trtl_ptr == rbit_ptr)
            return 1;
        rbit++;
        rbit_ptr = rbit_ptr -> next;
        if (If_pow2 (rbit))
        {
            trtl_ptr = rbit_ptr;
            rbit++;
            rbit_ptr = rbit_ptr -> next;
        }
    }
    return 0;
}

int main (void)
{
    struct node_t * top = (struct node_t *) calloc (1, sizeof (struct node_t *));
    struct node_t * first = (struct node_t *) calloc (1, sizeof (struct node_t *));
    struct node_t * second = (struct node_t *) calloc (1, sizeof (struct node_t *));
    struct node_t * third = (struct node_t *) calloc (1, sizeof (struct node_t *));


    top -> next = first;
    first -> next = second;
    second -> next = third;
    third -> next = second;

    printf ("Loop in a list: %d\n", list_is_a_loop (top));

    return 0;
}
