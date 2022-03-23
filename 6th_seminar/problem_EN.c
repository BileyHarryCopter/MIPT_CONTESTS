#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ITER 4000
#define accur 0.000001
#define accur_strih 0.001
#define pi 3.1415

typedef struct koefs
{
    double a;
    double b;
    double c;
} koefs;

double func (koefs kaef, double x)
{
    return ((kaef.a)*x*x*sin(x) + (kaef.b)*x*cos(x) + (kaef.c));
}

double func_shtrih (koefs kaef, double x)
{
    return (2*kaef.a - kaef.b)*x*sin(x) + (kaef.a * x*x + kaef.b)*cos(x);
}

double my_mod (double x)
{
    if (signbit (x))
        return -x;
    return x;
}
/*
double newton_met (koefs kaef, double x)
{
    double f_shtrih, function = 0.0;
    function = func (kaef, x);
    if (my_mod (function) < accur)
        return x;
    f_shtrih = func_shtrih (kaef, x);
    if (my_mod (f_shtrih) < accur_strih)
        return 0.0;
    return newton_met (kaef, x - (double)function / f_shtrih);
}
*/
double newton_met (koefs kaef, double x)
{
    int i = 0;
    double f_shtrih, function = 0.0;
    function = func (kaef, x);
    f_shtrih = func_shtrih (kaef, x);
    while (my_mod (function) > accur)
    {
        if (my_mod (f_shtrih) > accur_strih && i < MAX_ITER)
        {
            x -= (double)function / f_shtrih;
            function = func (kaef, x);
            f_shtrih = func_shtrih (kaef, x);
        }
        else
            break;
        i++;
    }
    return function;
}

int main (void)
{
    koefs kaef = {};
    double x_init = 0.0;
    scanf ("%lf %lf %lf %lf", &(kaef.a), &(kaef.b), &(kaef.c), &x_init);

    printf ("%.5lf\n", newton_met (kaef, x_init));

    return 0;
}
