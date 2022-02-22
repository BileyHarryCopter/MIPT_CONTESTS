#include <stdio.h>
#include <stdlib.h>

#define N 100

struct _Decimal {
    char a[N];       // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;  // наибольшая степень десяти
};

typedef struct _Decimal Decimal;

Decimal zero = {{0}, 0};

void mult10 (Decimal * res, const Decimal * a)
{
    unsigned int i;

    if (a->a[a->n] == 0)
    {
        res->n = 0;
        res->a[res->n] = 0;
    }
    else
    {
        (res->a[0]) = 0;
        (res->n) = (a->n) + 1;
        for (i = 1; i < (res->n) + 1; i++)
        {
            (res->a[i]) = (a->a[i -1]);
        }
    }
}

void print (Decimal * numb)
{
    int i;
    i = (numb->n);
    while (i >= 0)
    {
        printf ("%u", (numb->a[i]));
        i--;
    }
}

int main(void)
{
    Decimal a = {{7, 4, 1, 0, 2, 4, 4, 7, 2, 7, 9, 6, 4, 7, 2, 6, 8, 8, 5, 3, 6, 9, 8, 9, 6, 6, 8}, 26};
    Decimal res;

    mult10(&res, &a);          // res = a*10 = 147*10 = 1470

    print (&a);            //   print 866989635886274697274420147
    printf ("\n");
    print (&res);          //   print 8669896358862746972744201470
    printf ("\n");

    return 0;
}
