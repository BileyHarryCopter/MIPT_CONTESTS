#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int compare (const void * x1, const void * x2)
{
  return (*(int*)x1 - *(int*)x2);
}

int * nominal_init (int N)
{
    int i = 0;
    int * arnom;
    arnom = (int *) calloc (N, sizeof (int));
    for (i = 0; i < N; i++)
    {
        scanf ("%d", arnom + i);
    }
    qsort (arnom, N, sizeof (int), compare);
    return arnom;
}

int * dynmass (int sum, int * nominals, int mtype)
{
    int i = 0, j = 0, k = 0, min = 0;
    int * dynam;
    min = 10000;
    dynam = (int *) calloc (sum + 1, sizeof (int));
    for (i = 0; i < sum + 1; i++)
    {
        for (k = 0; k < mtype; k++)
        {
            if (i > * (nominals + k))
            {
                if ((* (dynam + i - * (nominals + k)) != 0) && (* (dynam + i - * (nominals + k)) < min))
                {
                    min = * (dynam + i - * (nominals + k));
                    * (dynam + i) = min + 1;
                }
            }
            else
            {
                break;
            }
        }
        if (i == * (nominals + j))
        {
            * (dynam + i) = 1;
            j++;
        }
        min = 10000;
    }
    return dynam;
}



int main (void)
{
    int sum = 0, mtype = 0;
    int * nominal;
    int * minumb;

    scanf ("%d", &sum);
    scanf ("%d", &mtype);

    nominal = nominal_init (mtype);
    minumb = dynmass (sum, nominal, mtype);
    /*
    for (int i = 0; i < sum + 1; i++)
    {
        printf ("%d   %d\n", i, * (minumb + i));
    }
    */
    printf ("%d\n", * (minumb + sum));

    free (nominal);
    free (minumb);
    return 0;
}
