#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct namednum {
    char *name;
    int number;
};


#include <string.h>
// TODO: ваш код здесь
//  arr - указатель на начало массива из указателей на структуры
//  arrlen - длина массива или количество указателей

struct namednum {
    char *name;
    int number;
};

#include <string.h>
void fixupstrings(struct namednum *arr, int arrlen)
{
    int i, j, length;
    for (i = 0; i < arrlen; i++)
    {
        for (j = 0; j < arrlen; j++)
        {
            if (j == i || arr[i].name == NULL)
            {
                continue;
            }
            if (arr[i].name == arr[j].name)
            {
                length = strlen (arr[i].name) + 1;
                arr[j].name = (char *) calloc (length, sizeof (char));
                strcpy (arr[j].name, arr[i].name);
            }
        }
    }
}

#include <string.h>

int comparator1 (const void * x1, const void * x2)
{
    struct namednum * str1 = (struct namednum *) x1;
    struct namednum * str2 = (struct namednum *) x2;
    return (int)((str1 -> name) - (str2 -> name));
}

int comparator2 (const void * x1, const void * x2)
{
    struct namednum * str1 = (struct namednum *) x1;
    struct namednum * str2 = (struct namednum *) x2;
    return (int)((str1 -> number) - (str2 -> number));
}

void fixupstrings(struct namednum *arr, int arrlen)
{
    int i, j, length, pos;
    i = 1;

    qsort (arr, arrlen, sizeof (struct namednum *), comparator1);

    while (i < arrlen)
    {
        if (arr[i].name == NULL)
        {
            i++;
            continue;
        }
        if (arr[i].name == arr[i - 1].name)
        {
            length = strlen (arr[i - 1].name) + 1;
            arr[i - 1].name = (char *) calloc (length, sizeof (char));
            strcpy (arr[i - 1].name, arr[i].name);
        }
        i++;
    }

    qsort (arr, arrlen, sizeof (struct namednum *), comparator2);
}


int main (void)
{

    return 0;
}
