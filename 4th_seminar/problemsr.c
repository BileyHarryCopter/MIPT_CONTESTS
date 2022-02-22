#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void clear (char * symb)
{
    char c = getchar ();
    while (c == ' ' || c == '\n')
    {
        c = getchar ();
    }
    * symb = c;
}

char * str_init (int length)
{
    int i = 0;
    char * str = calloc (length, sizeof (char));
    clear (str);
    for (i = 1; i < length; i++)
    {
        * (str + i) = getchar ();
    }
    return str;
}

void str_rev (char * Str, char * str, int length)
{
    int i = 0, j = 0;
    char * first = 0;
    char * second = 0;
    first = strstr (Str, str);
    while ((first != 0) && (first != second))
    {
        second = strstr (Str, str);
        j = 0;
        for (i = length - 1; i >= 0; i--)
        {
            * (first + j) = * (str + i);
            j++;
        }
        first = strstr (Str, str);
    }
}

int main () {
    int length = 0, Length = 0;
    char * Str = 0;
    char * str = 0;


    scanf ("%d", &length);
    str = str_init (length);
    scanf ("%d\n", &Length);
    Str = str_init (Length);

    str_rev (Str, str, length);
    printf ("%s\n", Str);

    free (str);
    free (Str);
    return 0;
}
