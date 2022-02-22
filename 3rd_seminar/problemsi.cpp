#include <stdio.h>
#include <stdlib.h>

int moveright (int * arr, int key, int last)
{
    int i, k;
    i = 0;
    while ((key >= arr[i]) && (i <= last - 1))
    {
        i++;
    }
    for (k = last - 1; k >= i; k--)
    {
        arr[k + 1] = arr[k];
    }
    return i;
}

void insort (int * arr, unsigned len)
{
    unsigned i;
    for (i = 0; i < len; i++)
    {
        int key, pos;
        key = arr[i];
        unsigned pos = moveright (arr, key, i);
        arr[pos] = key;
    }
}

int main (void)
{
    int arr[10] = {1, 1, 3, 3, 4, 1, 9, 4, 9, 4};

    return 0;
}
