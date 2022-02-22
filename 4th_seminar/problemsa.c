#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char * strcat_r (char *dest, const char *src, int *bufsz);
int strsz (char * str);

int main () {

    int a = 10;
    char * str1 = (char *)calloc (a, sizeof (char));
    * str1 = 'x';
    * (str1 + 1) = 'y';
    * (str1 + 2) = 'n';

    char str2[] = " tybe";

    printf ("%s\n", strcat_r (str1, str2, &a));
    return 0;
}

int strsz (char * str)
{
    int length = 0;
    while (*(str + length) != 0)
    {
        length++;
    }
    return length;
}

char * strcat_r (char *dest, const char *src, int *bufsz)
{
    int length, Length, i;
    length = 0;
    Length = 0;
    i = 0;

    length = strsz (src);
    Length = strsz (dest);

    printf ("%d   %d\n", length, Length);

    if (length + Length + 1 > *bufsz)
    {
        dest = (char *)realloc ((char *) dest, length + Length + 1);
    }
    while (*(src + i) != 0)
    {
        *(dest + Length + i) = *(src + i);
        i++;
    }
    return dest;
}
