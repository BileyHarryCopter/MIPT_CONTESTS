#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// low - position of target element
// high - position of high element

unsigned partition (int *arr, unsigned low, unsigned high)
{
    int i, j, k;
    int * arr1;
    arr1 = (int *) calloc (high + low - 1, sizeof(int));
    k = low;
    j = 0;

    for (i = low + 1; i <= high; i++)
    {
        if (arr[i] <= arr[low])
        {
            arr1[k] = arr[i];
            k++;
        }
        else if (arr[i] > arr[low])
        {
            arr1[high - j] = arr[i];
            j++;
        }
    }
    arr1[k] = arr[low];
    for (i = low; i <= high; i++)
    {
        arr[i] = arr1[i];
    }
    free (arr1);
    return k;
}

void qsort_impl(int *arr, unsigned low, unsigned high)
{
    if (low >= high)
        return;

    unsigned pi = partition(arr, low, high);

    if (pi > low)
    {
        qsort_impl(arr, low, pi - 1);
    }
    qsort_impl(arr, pi + 1, high);
}

void qsort(int *arr, unsigned len)
{
    qsort_impl (arr, 0u, len - 1);
}

int main (void)
{
    unsigned N = 0;
    assert (scanf ("%u", &N) != 0);

    int * arr = (int *) calloc (N, sizeof (int));

    for (int i = 0; i < N; i++)
    {
        scanf ("%d", &arr[i]);
    }

    qsort (arr, N);

    for (int i = 0; i < N; i++)
    {
        printf ("%d ", arr[i]);
    }
    printf ("\n");

    free (arr);
    return 0;
}
