#include <stdio.h>
#include <stdlib.h>

int If_Prime (int n);
int prime (int N);


int main () {
    int N = 0;
    scanf("%d", &N);

    printf("%d\n", prime(N));

    return 0;
}

int prime (int N) {
    int sum = 0;
    int k = 2;
    while (sum < N) {
        if (If_Prime(k)) {
            sum++;
        }
        k++;
    }
    return k-1;
}

int If_Prime (int n) {
    if ((n == 2) || (n == 3)) {
        return 1;
    }
    if ((n < 2) || ((n % 2) == 0) || ((n % 3) == 0)) {
        return 0;
    }
    for (int i = 5; i*i <= n; i = i + 6) {
        if ( (n % i == 0) || (n % (i + 2) == 0) ) {
            return 0;
        }
    }
    return 1;
}
