#include <stdio.h>
#include <stdlib.h>

#define HASH_MAX 100;

typedef int (*get_hash_t)(const char *s);
// подсчитать количество коллизий функции f над
// массивом strs
int clscount (char **strs, int n, get_hash_t f)
{
    int i;
    int cls_counter = 0;
    int hash[HASH_MAX] = {0};

    for (i = 0; i < HASH_MAX; i++)
    {
        hash[i] = -1;
    }

    for (i = 0; i < n; i++)
    {
        hash[f(strs[i])]++;
    }

    for (i = 0; i < HASH_MAX; i++)
    {
        if (hash[i] > 0)
        {
            cls_counter += hash[i];
        }
    }
    return cls_counter;
}
