#include <stdio.h>
#include <stdlib.h>

typedef int (*generator_t)(int);

//  определяет длину петли в генераторе
//  с помощью алгоритма Флойда
unsigned cycle_len (generator_t gen)
{
    unsigned len;
    unsigned position;

    position = gen (gen (gen (0)));
    len = 2;

    if (gen(0) == gen(gen(0)))
    {
        return 1;
    }

    while (gen (position) != gen (0) && gen (gen (position)) != gen (gen (0)))
    {
        len++;
        position = gen (position);
    }

    return len + 1;
}

int Generator_1 (int x)
{
    return (x + 2) % 5;
}

int Generator_2 (int x)
{
    return (3 * x + 2) % 5 + 4;
}
int Generator_3 (int x)
{
    return (x + 2) % 5 + 3;
}

int main (void)
{
    printf ("Period in gen_1: %d\n", cycle_len(Generator_1));
    printf ("Period in gen_2: %d\n", cycle_len(Generator_2));
    printf ("Period in gen_3: %d\n", cycle_len(Generator_3));
    return 0;
}
