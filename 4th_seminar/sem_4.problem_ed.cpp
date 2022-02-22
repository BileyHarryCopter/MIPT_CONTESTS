#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
                        //ЗАБРОШЕНО ДО ЛУЧШИХ ВРЕМЕН
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//

int min_3 (int a, int b, int c)
{
    int min, i;
    min = a;
    if (b < min)
    {
        b = min;
        if (c < min)
        {
            return c;
        }
        return b;
    }
    else if (c < min)
    {
        return c;
    }
    return a;

}

unsigned Find_mindir (unsigned c_add, unsigned c_del, unsigned c_swap,
                      unsigned len_1, unsigned len_2, char * str1, char * str2)
{
    //  ld = length of direction
    int i, j;
    int * ld_y;
    int * ld_x;


}

int main (void)
{
    unsigned i, c_add, c_del, c_swap, len_1, len_2, disdir = 0;
    char * str_1;
    char * str_2;
    assert (scanf ("%u %u %u", &c_add, &c_del, &c_swap) != 0);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
    scanf ("%u", &len_1);
    str_1 = (char *) calloc (len_1, sizeof (char));
    for (i = 0; i < len_1; i++)
    {
        scanf ("%c", &str_1[i]);
    }
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
    scanf ("%u", &len_2);
    str_2 = (char *) calloc (len_2, sizeof (char));
    for (i = 0; i < len_2; i++)
    {
        scanf ("%c", &str_2[i]);
    }
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//

    disdir = Find_mindir (c_add, c_del, c_swap, len_1, len_2, str_1, str_2);

    return 0;
}
/*
ld_x = (int *) calloc (len_1 + 1, sizeof (int));
for (i = 0; i < len_1 + 1; i++)
{
    ld_y + i = (int *) calloc (len_2 + 1, sizeof (int));
}


for (i = 0; i < len + 1; i++)
{
    free (ld_y + i);
}
free (ld_x);
*/
