#include <stdio.h>
#include <stdlib.h>

struct list_t {
  struct list_t *next;
  int data;
};

struct list_t * List_init (FILE * file)
{
    int x;
    struct list_t * top;
    struct list_t * help;
    x = 0;
    top = (struct list_t *) calloc (1, sizeof (struct list_t));
    help = top;
    while (fscanf (file, "%d", &x) != EOF)
    {
        help->next = (struct list_t *) calloc (1, sizeof (struct list_t));
        help = help->next;
        help->data = x;
    }
    help->next = NULL;
    rewind (file);
    free (help);
    return top;
}

void Delete_list (struct list_t *top)
{
    struct list_t * first;
    struct list_t * second;
    first = (struct list_t *) calloc (1, sizeof (struct list_t));
    second = (struct list_t *) calloc (1, sizeof (struct list_t));
    first = top;
    second = first -> next;
    while (second != NULL)
    {
        free (first);
        first = second;
        second = first -> next;
    }
    free (first);
    free (second);
}

struct list_t *odd_even (struct list_t *top)
{
    // TODO: ваш код здесь
    struct list_t * first;
    struct list_t * second;
}

int main (void)
{

    return 0;
}
