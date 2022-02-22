#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
    int sum = 0;
    char c = 0;
    while ((c = getchar ()) != EOF)
    {
        sum += c;
    }
    printf ("%d\n", sum);
    return 0;
}
