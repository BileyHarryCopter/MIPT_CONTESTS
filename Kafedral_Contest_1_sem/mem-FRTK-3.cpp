#include <stdio.h>
#include <stdlib.h>

struct _Decimal {
    char * a;          // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
    unsigned int n;    // наибольшая степень десяти
    unsigned int size; // размер выделенной динамической памяти в а (можно это поле не использовать)
};

typedef struct _Decimal Decimal;

void set_init (Decimal ** numb, const char * str)
{
    int size, i, k;
    Decimal * numf = 0;
    size = 0;
    i = 0;
    k = 0;
    *numb = (Decimal *) malloc (sizeof (Decimal));
    numf = *numb;

    while (*(str + size) != '\0')
    {
        size++;
    }

    numf->n = size - 1;
    numf->size = size;
    numf->a = (char *) malloc (size);


    for (k = numf->size; k >= 1; k--)
    {
        *(numf->a + i) = *(str + k - 1);
        //printf ("%d     %c\n", i, *(numf->a + i));
        i++;
    }
}

void print (Decimal * numb)
{
    int i;
    i = 0;
    i = (numb->n);
    while (i >= 0)
    {
        printf ("%c", (numb->a[i]));
        i--;
    }
}

void num_free (Decimal * numb)
{
    free (numb->a);
    free (numb);
}

Decimal * mult10 (const Decimal * arr)
{
    unsigned i;
    Decimal * res = 0;
    i = 0;
    res = (Decimal *) malloc (sizeof (Decimal));

    if (*(arr->a + arr->n) == '0')
    {
        res->n = 0;
        res->size = 1;
        res->a = (char *) malloc (1);
        *(res->a) = '0';
    }
    else
    {
        res->n = (arr->n) + 1;
        res->size = (arr->size) + 1;
        res->a = (char *) malloc (res->size);

        * (res->a) = '0';
        while (i < (arr->n + 1))
        {
            * (res->a + i + 1) = *(arr->a + i);
            i++;
        }
    }
    return res;
}

int main (void)
{
    Decimal * arr = 0;
    Decimal * res = 0;

    set_init (&arr, "1234567890");
    res = mult10 (arr);

    print (arr);
    printf ("\n");
    print (res);
    printf ("\n");

    num_free (arr);
    num_free (res);
    return 0;
}
