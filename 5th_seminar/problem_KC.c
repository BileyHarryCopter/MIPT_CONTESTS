#include <stdio.h>
#include <stdlib.h>

int get_hash(const char *start, const char *fin);
int update_hash (int current, int n, char cprev, char cnext);
unsigned long long pow_mod (unsigned n, unsigned k, unsigned m);



int istrcmp (const char *needle, const char *ip)
{
    while (*needle != '\0')
    {
        if (*needle != *ip)
            return -1;
        needle++;
        ip++;
    }
    return 0;
}
int rabin_karp (const char *needle, const char *haystack)
{
    unsigned n, target, cur, status = -1, count = 0, left = 0, right = strlen(needle);

    target = get_hash (needle, needle + right);
    cur = get_hash (haystack, haystack + right);
    n = pow_mod (R, right - 1, Q);

    while (haystack[right] != '\0')
    {
        if (cur == target)
        {
            if (istrcmp (needle, haystack + left) == 0)
            {
                return left;
            }
        }
        right++;
        left++;
        cur = update_hash (cur, n, haystack[left - 1], haystack[right - 1]);
    }
    return -1;
}


int main (void)
{

    return 0;
}
