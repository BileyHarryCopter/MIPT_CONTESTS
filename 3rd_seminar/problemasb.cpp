#include <stdio.h>
#include <stdlib.h>

int arrpopcount (const unsigned char *parr, int len)
{
    int i, j, sum;
    char temp;
    j = 7;
    sum = 0;
    temp = 0;
    for (i = 0; i < len; i++)
    {
        temp = * (parr + i);
        while (j >= 0)
        {
            sum += (temp >> j) & 1;
            j--;
        }
        j = 7;
    }
    return sum;
}

int main (void)
{
    int len = 5;
    unsigned char parr[5] = {1, 2, 4, 8, 16};
    printf ("Sum of bytes: %d\n", arrpopcount (parr, len));
    return 0;
}
