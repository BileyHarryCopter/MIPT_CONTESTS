#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv) {

    char ** beer;
    int i, status;
    i = 0;
    status = 1;

    beer = (char **) calloc (argc + 1, sizeof (char *));

    while (i < argc)
    {
        beer[i] = argv[i];
        if (* (beer[i]) == '-' && * (beer[i] + 1) == 'r')
        {
            status = -1;
        }
        if (** (beer + i) == '-')
        {
            * beer[i] = '+';
        }
        else if (** (beer + i) == '+')
        {
            * beer[i] = '-';
        }
        i++;
    }
    if (status == -1)
    {
        for (i = argc - 1; i > -1; i--)
        {
            printf ("%s ", beer[i]);
        }
    }
    else
    {
        for (i = 0; i < argc; i++)
        {
            printf ("%s ", beer[i]);
        }
    }
    printf ("\n");

    free (beer);
    return 0;
}
