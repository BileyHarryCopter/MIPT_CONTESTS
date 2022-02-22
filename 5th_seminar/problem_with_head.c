#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum ways {
    PRE = 1,
    IN
};

int * data_fill (int *buff, int size, int mode);
int * bpss_fill (int *preord, int *inord, int size);
void print_shit (int size, int *bypass, int *preord);

int main (void)
{
    int      *buff;
    int    *preord;
    int     *inord;
    int    *bypass;
    int    pos = 0;
    int   size = 0;
    assert (scanf ("%d", &size));

    size = size * 2;
    buff = (int *) calloc (size, sizeof (int));

    for (pos = 0; pos < size; pos++)
    {
        assert (scanf ("%d", buff + pos));
    }

    preord = data_fill (buff, size / 2, PRE);

    inord  = data_fill (buff, size / 2, IN);

    bypass = bpss_fill (preord, inord, size);

    print_shit (size / 2, bypass, preord);

    return 0;
}

int * data_fill (int *buff, int size, int mode)
{
    int   pos = 0;
    int    ip = 0;
    int *data = (int *) calloc (size, sizeof (int));

    if (mode == IN)
    {
        pos = size;
        size = size * 2;
    }
    for (; pos < size; pos++)
    {
        data[ip] = buff[pos];
        ip++;
    }
    return data;
}

int * bpss_fill (int *preord, int *inord, int size)
{
    int ip      = 0;
    int ip_pre  = 0;
    int ip_inr  = 0;
    int border  = preord[ip];
    int *bypass = (int *) calloc (size, sizeof (int));

    for (ip = 0; ip < size; ip++)
    {
        if (inord[ip_pre] == border)
        {
            bypass[ip] = 1;
            ip++;
            ip_pre++;
            border = preord [ip_pre];
            while (ip_inr < ip_pre)
            {
                bypass[ip] = 0;
                ip++;
                ip_inr++;
            }
            ip--;
            continue;
        }
        bypass[ip] = 1;
        ip_pre++;
    }
    return bypass;
}

void print_shit (int size, int *bypass, int *preord)
{
    int pos = 0;
    printf ("%d ", size);

    size = 2 * size;

    while (pos < size)
    {
        printf ("%d ", bypass[pos]);
        pos++;
    }
    pos = 0;
    size = size / 2;
    while (pos < size)
    {
        printf ("%d ", preord[pos]);
        pos++;
    }
    printf ("\n");
}
