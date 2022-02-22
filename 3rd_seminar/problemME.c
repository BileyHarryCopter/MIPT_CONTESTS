#include <stdio.h>
#include <stdlib.h>

int check_majority (int const * parr, int length, int maj) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        if (maj == * (parr + i)) {
            sum++;
        }
    }
    return (sum > length/2) ? maj : -1;
}

int majority_element (int const * parr, int length) {
    int majL, majR;
    // создать прототип исходного массива
    int * arr = (int *) calloc (length, sizeof (int));

    if (length == 1) {
        return * parr;
    }
    if (length == 2) {
        if (* parr == * (parr + 1)) {
            return * parr;
        }
        if (* parr != * (parr + 1)) {
            // not so fast
            return -1;
        }
    }
    // printf ("%d\n", length);

    for (int i = 0; i < length; i++)
    {
        * (arr + i) = * (parr + i);
    }

    majL = majority_element (arr, length/2);
    majR = majority_element (arr + length/2, length/2 + length%2);

    if (majL == majR) {
        return majL;
    }
    if (majL == -1) {
        return check_majority (parr, length, majR);
    }
    if (majR == -1) {
        return check_majority (parr, length, majL);
    }

    if (majR != majL) {
        int a = check_majority (parr, length, majR);
        int b = check_majority (parr, length, majL);
        if (a != -1) {
            return a;
        }
        if (b != -1) {
            return b;
        }
    }
    return -1;
    free (arr);
}

int main () {

    int arr[6] = {9, 1, 1, 9, 2, 2};

    printf ("%d\n", majority_element (arr, 6));

    return 0;
}
