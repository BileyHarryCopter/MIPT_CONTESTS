#include <stdio.h>
#include <stdlib.h>

void insort_i (int * arr, int length, int pos)
{
    int min, temp, k, min_i;
    min_i = pos;
    min = *(arr + pos);
    for (k = pos; k < length; k++)
    {
        if (*(arr + k) < min)
        {
            min = *(arr + k);
            min_i = k;
        }
    }
    temp = *(arr + pos);
    *(arr + pos) = *(arr + min_i);
    *(arr + min_i) = temp;
}

int main (void)
{
    int length, pos, k;
    int * arr;
    length = 0;
    pos = 0;

    scanf ("%d", &length);
    arr = (int *) calloc (length, sizeof (int));

    for (k = 0; k < length; k++)
    {
        scanf ("%d", (arr + k));
    }

    scanf ("%d", &pos);

    insort_i (arr, length, pos);

    for (k = 0; k < length; k++)
    {
        printf ("%d ", *(arr + k));
    }
    printf ("\n");
    free (arr);
    return 0;
}
