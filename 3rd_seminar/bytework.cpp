#include <stdio.h>
#include <stdlib.h>

int Max_Byte (unsigned long long numb)
{
    int i = 63;
    while ((((numb >> i) & 1) != 1)&&(i > -1))
    {
        i--;
    }
    return (i == -1) ? -1 : i;
}

int main (void) {
    unsigned long long numb = 10;
    scanf ("%llu", &numb);
    printf ("%d\n", Max_Byte (numb));
    return 0;
}
