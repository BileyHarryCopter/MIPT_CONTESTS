#include <stdio.h>
#include <stdlib.h>

int iseven (int x)
{
    return (x % 2 == 0) ? 1 : 0;
}

struct node_t * read_list (FILE * inp)
{
    int x = 0;
    struct node_t * top;
    struct node_t * help;
    top =  (struct node_t *) calloc (1, sizeof (struct node_t));
    help = (struct node_t *) calloc (1, sizeof (struct node_t));
    help = top;
    // help -> next = (struct node_t *) calloc (1, sizeof (struct node_t));
    while (fscanf (inp, "%d", &x) != EOF)
    {
        if (iseven (x) == 1)
        {
            help -> next = (struct node_t *) calloc (1, sizeof (struct node_t));
            help -> data = x;
            help = help -> next;
        }
    }
    rewind (inp);
    while (fscanf (inp, "%d", &x) != EOF)
    {
        if (iseven (x) == 0)
        {
            help -> next = (struct node_t *) calloc (1, sizeof (struct node_t));
            help -> data = x;
            help = help -> next;
        }
    }
    help -> next = NULL;
    fclose (inp);
    free (help);
    return top;
}

void delete_list (struct node_t *top)
{
    struct node_t * first;
    struct node_t * second;
    first = (struct node_t *) calloc (1, sizeof (struct node_t));
    second = (struct node_t *) calloc (1, sizeof (struct node_t));
    first = top;
    second = top -> next;
    while (second != NULL)
    {
        second = first -> next;
        free (first);
        first = second;
        second = first -> next;
    }
}
