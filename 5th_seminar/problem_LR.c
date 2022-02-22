#include <stdio.h>
#include <stdlib.h>

struct node_t {
    struct node_t * next;
    int data;
};
/*
struct node_t * reverse (struct node_t * top)
{
    struct node_t * xs;
    if (NULL == top)
        return NULL;
    if (NULL == top->next)
        return top;
    xs = reverse (top->next);
    top->next->next = top;
    top->next = NULL;
    return xs;
}
*/
struct node_t * reverse (struct node_t * top)
{
    struct node_t * new_top = (struct node_t *) calloc (1, sizeof (struct node_t));
    struct node_t * intrmdt = (struct node_t *) calloc (1, sizeof (struct node_t));

    if (top == NULL)
    {
        return NULL;
    }
    else if(top->next == NULL)
    {
        return top;
    }
    else
    {
        new_top = top;
        intrmdt = top->next;
        top = intrmdt;
        new_top->next = NULL;

        while (top->next != NULL)
        {
            //printf ("SEX\n");
            intrmdt = top->next;
            top->next = new_top;
            new_top = top;
            top = intrmdt;
        }
    }
    top->next = new_top;
    new_top = top;
    return new_top;
}

int main (void)
{
    struct node_t * top = (struct node_t *) calloc (1, sizeof (struct node_t));
    struct node_t * first = (struct node_t *) calloc (1, sizeof (struct node_t));
    struct node_t * second = (struct node_t *) calloc (1, sizeof (struct node_t));
    struct node_t * third = (struct node_t *) calloc (1, sizeof (struct node_t));

    top->next = first;
    first->next = second;
    second->next = third;
    third->next = NULL;

    top->data = 2;
    top->next->data = 6;
    top->next->next->data = 4;
    top->next->next->next->data = 1;

    printf ("BEFORE REVERSE: %d -> %d -> %d -> %d\n", top->data, top->next->data,
                                                      top->next->next->data,
                                                      top->next->next->next->data);

    top = reverse (top);

    printf ("AFTER REVERSE: %d -> %d -> %d -> %d\n", top->data, top->next->data,
                                                      top->next->next->data,
                                                      top->next->next->next->data);


    return 0;
}
