#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


//  требуется отсортировать положительные, а остальные оставить на свох местах
void frtk_sort (double * arr0, unsigned length)
{
    unsigned i, j, len_pos;
    double temp;
    double * arr_pos;
    double ** ptr_pos;
    len_pos = 0;
    arr_pos = (double *) calloc (length + 1, sizeof (double));
    ptr_pos = (double **) calloc (length + 1, sizeof (double *));

    for (i = 0; i < length; i++)
    {
        if (*(arr0 + i) > 0)
        {
            *(ptr_pos + len_pos) = arr0 + i;
            *(arr_pos + len_pos) = * (arr0 + i);
            len_pos++;
        }
    }

    // sorting //
    for (i = 0; i < len_pos; i++)
    {
        for (j = 0; j < len_pos - i - 1; j++)
        {
            if (*(arr_pos + j) - * (arr_pos + j + 1) > 0)
            {
                temp = *(arr_pos + j);
                *(arr_pos + j) = *(arr_pos + j + 1);
                *(arr_pos + j + 1) = temp;
            }
        }
    }

    for (i = 0; i < len_pos; i++)
    {
        ** (ptr_pos + i) = * (arr_pos + i);
    }

    free (arr_pos);
    free (ptr_pos);
}

int main (void)
{
    unsigned length;
    double * arr0;

    length = 0;

    arr0 = (double *) calloc (1000, sizeof (double));

    while  (scanf ("%lf", (arr0 + length))!= EOF)
    {
        length++;
    }

    frtk_sort (arr0, length);


    for (int i = 0; i < length; i++)
    {
        printf ("%.3lf ", * (arr0 + i));
    }

    printf ("\n");

    free (arr0);
    return 0;
}
