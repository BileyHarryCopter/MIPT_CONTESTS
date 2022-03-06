#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX 23

void generate (float *numb)
{
    int obraz, pos = 0;
    memcpy (&obraz, numb, sizeof (float));

    for (pos = 1; pos < MAX; pos++)
    {
        if (pos % 2 == 1)
        {
            obraz = obraz ^ (1 << pos);
        }
    }
    memcpy (numb, &obraz, sizeof (float));
}

int main (void)
{
    float numb = 0.0;

    scanf ("%f", &numb);

    generate (&numb);

    printf ("%f\n", numb);

    return 0;
}
