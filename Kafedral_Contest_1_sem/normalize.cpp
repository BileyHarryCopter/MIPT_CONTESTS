#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern void normalize_path (char * path)
{
    int i, k, size, length;
    i = 0;
    k = 0;
    size = 0;
    length = 0;
    size = strlen (path);

    while (*(path + i) != '\0')
    {
        if (*(path + i) == '/')
        {
            length = 0;
            i++;
            if (*(path + i) == '/')
            {
                while (*(path + i) == '/')
                {
                    length++;
                    i++;
                }

                if (*(path + i) == '\0')
                {
                    i--;
                }
                k = i;

                while (*(path + k) != '\0')
                {
                    *(path + k - length) = *(path + k);
                    k++;
                }

                if (*(path + k) == '\0')
                {
                    *(path + k - length) = '\0';
                }
                i -= length;
                length = 0;
            }
            else if (*(path + i) == '.')
            {
                length = 0;
                i++;
                if (*(path + i) == '/')
                {
                    length = 2;
                    k = i;
                    while (*(path + k) != '\0')
                    {
                        *(path + k - length) = * (path + k);
                        k++;
                    }

                    if (*(path + k) == '\0')
                    {
                        *(path + k - length) = '\0';
                    }
                    i -= length;
                    length = 0;
                }
                else if (*(path + i) == '.')
                {
                    length = 4;
                    k = i;
                    while (*(path + k - 3) != '/' && (k != 3))
                    {
                        length++;
                        k--;
                    }
                    i += 2;
                    k = i;
                    while (*(path + k) != '\0')
                    {
                        *(path + k - length) = * (path + k);
                        k++;
                    }
                    if (*(path + k) == '\0')
                    {
                        *(path + k - length) = '\0';
                    }
                    i -= length;
                    length = 0;
                }
            }
        }
        i++;
    }
}

int main (void)
{
    char cp[] = "var/log////jexe/../err/./yrty/";
    printf ("%s\n", cp);
    normalize_path (cp);
    printf ("%s\n", cp);
    return 0;
}
