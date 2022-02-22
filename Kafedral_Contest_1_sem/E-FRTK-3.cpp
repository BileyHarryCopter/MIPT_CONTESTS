#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// на dst память уже выделена
char * convert (char * dst, const char * src)
{
    unsigned i, k, sin;
    i = 0;
    sin = 0;
    k = 0;

    if (src != NULL)
    {
        while ((isspace (* (src + i)) != 0) && *(src + i) != 0)
        {
            i++;
        }

        while (*(src + i) != '\0')
        {
            *(dst + k) = *(src + i);
            sin++;
            i++;
            k++;
        }

        if (sin != 0)
        {
            k--;
        }

        while (isspace (* (dst + k)) != 0)
        {
            *(dst + k) = '\0';
            k--;
        }
        k++;
        *(dst + k) = '\0';

        return dst;
    }

    return NULL;
}
/*
int main (void)
{

    char d[100] = {0};

    char * c = 0;

    printf("_%s_\n", convert(d, "fggff"));

    return 0;
}
*/
