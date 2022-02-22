#include <stdio.h>
#include <stdlib.h>

int Max_length (int * arr, int position)
{
    int length = 0;
    for (int i = 0; i < position; i++)
    {
        if (arr[i] < arr[position])
        {
            int len = Max_length (arr, i);
            if (len > length)
            {
                length = len;
            }
        }
        printf ("%d ", arr[i]);
    }
    printf ("\n");
    return length + 1;
}


int main (void)
{
    int k, length = 0;
    int * arr = 0;
    scanf ("%d", &k);

    arr = (int *) calloc (k, sizeof (int));

    for (int j = 0; j < k; j++)
    {
        scanf ("%d", &arr[j]);
    }

    length = Max_length (arr, k - 1);

    printf ("Length of max podpos: %d\n", length);

    free (arr);
    return 0;
}
