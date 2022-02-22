#include <stdio.h>
#include <stdlib.h>

int Max (int a, int b) {
    return (a - b >= 0) ? a : b;
}

// вернем указатель на int массив из коэффициентов
void PolyPow (int length1, int length2, int * arr1, int * arr2) {

    int Length = (length1 + length2 - 2) + 1;
    int * Arr;
    int bb;
    int * c;
    Arr = (int *) calloc ( Length, sizeof (int));

    for (int i = 0; i < length1; i++) {
        for (int j = 0; j < length2; j++) {
            for (int k = 0; k < Length; k++) {
                if (i + j == k) {
                    //printf ("%d * %d", *(arr1 + i), * (arr2 + j));
                    * (Arr + k) += (* (arr1 + i)) * (* (arr2 + j));
                }
            }
        }
    }
    //printf (" = ");
    bb = 0;
    c = Arr + Length;
    while (* c == 0) {
        bb++;
        c--;
    }

    for (int i = 0; i < Length - bb + 1; i++) {
        printf ("%d ", * (Arr + i));
        // решить проблему с 0

    }
    printf ("\n");
    free (Arr);
}


int main (void) {
    int length1 = 0;
    int length2 = 0;
    int * arr1;
    int * arr2;

    scanf ("%d %d", &length1, &length2);

    arr1 = (int *) calloc (length1, sizeof (int));
    arr2 = (int *) calloc (length2, sizeof (int));

    for (int i = 0; i < length1; i++) {
        scanf ("%d", arr1 + i);
    }
    for (int j = 0; j < length2; j++) {
        scanf ("%d", arr2 + j);
    }

    PolyPow (length1, length2, arr1, arr2);

    free (arr1);
    free (arr2);
    return 0;
}
