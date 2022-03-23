#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define accur 0.00001
#define pi 3.1415

typedef struct koefs
{
    double a;
    double b;
    double c;
} koefs;

double func (koefs kaef, double x)
{
    return (kaef.a)*x*x*sin(x) + (kaef.b)*x*cos(x) + (kaef.c);
}

int mod (int N)
{
    if (N < 0)
        return -N;
    return N;
}

/*
double dih_gap (double min, double max, koefs kaef)
{
    if (max - min < accurance)
    {
        if (signbit(func (kaef, min)) == 0 && signbit(func (kaef, max)) == 1
            || signbit(func (kaef, min)) == 1 && signbit(func (kaef, max)) == 0)
            return func (kaef, (max + min)/2);
        else
            return 0.0;
    }
    else if (signbit (func (kaef, min)) != signbit (func (kaef, max)))
    {
        if (signbit (func (kaef, min)) != signbit (func (kaef, (min + max)/2)))
            return dih_gap (min, (min + max)/2, kaef);
        else if (signbit (func (kaef, (min + max)/2)) != signbit (func (kaef, max)))
            return dih_gap ((min + max)/2, max, kaef);
    }
    return 0.0;
}
*/

double dih_gap (koefs kaef, int edge)
{
    int min = -edge;
    int max =  edge;
    while (max - min > accur)
    {
        if (signbit (func (kaef, min) != signbit (func (kaef, min + max)/2)))
        {
            min = min;
            max = (min + max) / 2;
            continue;
        }
        else if (signbit (func (kaef, (min + max)/2)) != signbit (func (kaef, max)))
        {
            max = max;
            min = (max + min) / 2;
            continue;
        }
        else
            break;
    }
    if (signbit(func (kaef, min)) != signbit(func (kaef, max)))
        return func (kaef, (max + min)/2);
    else
        return 0.0;
}

int main (void)
{
    koefs kaef = {};
    int N = 0;
    double ans = 0.0;
    scanf ("%d %lf %lf %lf", &N, &(kaef.a), &(kaef.b), &(kaef.c));

    //  printf ("%lf %lf %lf\n", kaef.a, kaef.b, kaef.c);

    printf ("sign: %d\n", signbit (1.344));

    ans = dih_gap (kaef, mod (N));
    printf ("%.5lf\n", ans);

    return 0;
}
