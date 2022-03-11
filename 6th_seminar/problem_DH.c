#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define accurance 0.0001

typedef struct koefs
{
    double a;
    double b;
    double c;
} koefs;

double func (koefs kaef, double x)
{
    return (kaef.a)*x*x*sin(x) + (kaef.b)*x + (kaef.c);
}

double dih_gap (double min, double max, koefs kaef)
{
    if (max - min < accurance)
    {
        if (signbit(func (kaef, min)) == 0 && signbit(func (kaef, max)) == 1
            || signbit(func (kaef, min)) == 1 && signbit(func (kaef, max)) == 0)
            return func (kaef, (max + min)/2);
        else
            return 0;
    }
    if (signbit (func (kaef, min)) != signbit (func (kaef, max)))
    {
        if (signbit (func (kaef, min)) != signbit (func (kaef, (min + max) / 2)))
            return dih_gap (min, (min + max) / 2, kaef);
        else if (signbit (func (kaef, (min + max) / 2)) != signbit (func (kaef, max)) )
            return dih_gap ((min + max) / 2, max, kaef);
    }
    return 0;
}

int main (void)
{
    koefs kaef = {};
    int N = 0;
    double ans = 0.0;
    scanf ("%d %lf %lf %lf", &N, &(kaef.a), &(kaef.b), &(kaef.c));

    ans = dih_gap (-N, N, kaef);
    printf ("%.5lf\n", ans);

    return 0;
}
