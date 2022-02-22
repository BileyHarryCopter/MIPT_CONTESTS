#include <stdio.h>
#include <stdlib.h>

//  size = sizeof (struct)
//  n = number of structers

//  sizeof = size of structer
void swap (void * body1, void * body2, int size_e)
{
    int i;
    char * tmp = (char *) calloc (size_e, sizeof (char));
    for (i = 0; i < size_e; i++)
    {
        *(tmp + i) = *(char *)(body1 + i);
        *(char *)(body1 + i) = *(char *)(body2 + i);
        *(char *)(body2 + i) = *(tmp + i);
    }
    free (tmp);
}

void reverse(void *arr, int size, int n) {
    // TODO: ваш код здесь
    int i;
    for (i = 0; i < n/2; i++)
    {
        swap (arr + i * size, arr + (n - 1 - i)*size, size);
    }
}

int main (void)
{

    return 0;
}
