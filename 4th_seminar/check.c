#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main (void) {
    char * str = calloc (10, sizeof(char));
    for (int i = 0; i < 7; i++)
    {
        * (str + i) = 'A' + i;
    }
    str = (char *) realloc (str, 5*sizeof(char));
    * (str + 7) = 'E';
    printf ("%s\n", str);
    return 0;
}
