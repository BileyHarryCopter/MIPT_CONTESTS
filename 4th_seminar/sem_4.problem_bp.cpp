#include <stdio.h>
#include <stdlib.h>

int compare (const void * numb1, const void * numb2)
{
    return (*(unsigned *)numb1 - *(unsigned *)numb2);
}
unsigned Max_numb (unsigned capable, unsigned N, unsigned * wears)
{
    int i;
    unsigned cur_weight = 0;
    qsort (wears, N, sizeof (unsigned), compare);
    i = 0;
    while (i < N && cur_weight <= capable)
    {
        cur_weight += wears[i];
        i++;
    }
    return (i == N && cur_weight <= capable) ? i : i - 1;
}

int main (void)
{
    unsigned capable, i, N = 0;
    unsigned * wears = 0;

    scanf ("%d %d", &capable, &N);

    wears = (unsigned *) calloc (N, sizeof (unsigned));
    for (i = 0; i < N; i++)
    {
        scanf ("%d", &wears[i]);
    }

    printf ("%d\n", Max_numb (capable, N, wears));

    return 0;
}


//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
                    // ЗАБРОШЕНО НА НЕОПРЕДЕЛЕННЫЙ СРОК
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
/*
unsigned * Find_min (unsigned * arr, unsigned size)
{
    int i;
    unsigned * min = 0;
    min = arr;
    for (i = 0; i < size; i++)
    {
        if (arr[i] <= *min)
        {
            *min = arr[i];
            min = arr + i;
        }
    }
    return min;
}

unsigned Max_numb (unsigned capable, unsigned N, unsigned * wears)
{
    unsigned cur_weight, i;
    unsigned * ptr_wet = 0;
    ptr_wet = Find_min (wears, N);
    cur_weight += *ptr_wet;
    *ptr_wet = -1;          //    специально делаем переполнение
    for (i = 0; i < N && cur_weight <= capable; i++)
    {
        ptr_wet = Find_min (wears, N);
        cur_weight += *ptr_wet;
        *ptr_wet = -1;
    }
    return i;
}
*/
