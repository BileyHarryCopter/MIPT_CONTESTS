#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv) {

    FILE * file = fopen (argv[1], "w");

    char * string = fgetc (file);
    printf ("%c", string);
    /*
    while (fscanf (file, "%s", string) != 0)
    {
        printf ("%s ", string);
    }
    */

    fclose (file);
    return 0;
}
