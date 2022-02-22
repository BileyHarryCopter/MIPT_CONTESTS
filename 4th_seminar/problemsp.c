#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

char * replace (char *str, char const *from, char const *to);
int strsz (char * str);

int main (void) {

    char str1[] = "Hello, %username, how are you, %username?";
    const char str2[] = "%username";
    const char str3[] = "Eric, the Blood Axe";

    printf ("%s\n", str1);
    char * STR = replace (str1, str2, str3);
    printf ("%s\n", STR);

    free (STR);
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

char * replace (char *str, char const *from, char const *to)
{
    char * strnew;
    char * strpast;
    char * str_end;
    char * str_end1;
    int str_sz, from_sz, to_sz, strnew_sz, strpast_sz, delta_sz, status, i;

    strpast_sz = strsz (str);
    strnew_sz = strsz (str);
    from_sz = strsz (from);
    to_sz = strsz (to);

    //  initialization of the strings
    strpast = (char *) calloc (strpast_sz + 1, sizeof (char));
    for (i = 0; i < strpast_sz + 1; i++)
    {
        * (strpast + i) = * (str + i);
    }

    strnew = (char *) calloc (strnew_sz + 1, sizeof (char));
    for (i = 0; i < strpast_sz + 1; i++)
    {
        * (strnew + i) = * (strpast + i);
    }
    //  теперь  strpast выступает в роли str
    while (strstr (strpast, from) != 0)
    {
        strnew = (char *) realloc (strnew, strnew_sz + to_sz - from_sz + 1);
        str_end = strstr (strpast, from);
        str_end1 = strstr (strnew, from);
        delta_sz = str_end - strpast;

        if (to_sz < from_sz)
        {
            strnew_sz = strsz (strnew);
            for (i = 0; i < strpast_sz - delta_sz; i++)
            {
                * (str_end1 + to_sz + i) = * (str_end + from_sz + i);
            }
        }
        else
        {
            strnew_sz = strsz (strnew) + to_sz - from_sz;
            for (i = 0; i < strnew_sz - delta_sz; i++)
            {
                * (str_end1 + to_sz + i) = * (str_end + from_sz + i);
            }
        }

        for (i = 0; i < to_sz; i++)
        {
            * (str_end1 + i) = * (to + i);
        }
        * (strnew + strnew_sz + to_sz - from_sz) = 0;

        //  обновление информации о strpast
        strpast = (char *) calloc (strnew_sz + 1, sizeof (char));
        for (i = 0; i < strnew_sz + 1; i++)
        {
            * (strpast + i) = * (strnew + i);
        }
    }

    return strnew;
}
