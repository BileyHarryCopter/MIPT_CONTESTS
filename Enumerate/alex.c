#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Require(symb)           \
{                               \
    if (*s == symb)             \
        s++;                    \
    else                        \
        return NAN;             \
}

char *s = NULL;

double GetG (const char *str);
double GetE (void);
double GetT (void);
double GetP (void);
double GetN (void);

int main (int argc, char **argv)
{
    double val = GetG ("(2+25)/2$");

    if (val != val)
        printf ("SYNTAX ERROR\n");
    else
        printf ("ANSWER = %.2f\n", val);

    return 0;
}

double GetG (const char *str)
{
    s = (char *)str;
    double val = GetE ();

    Require ('$');

    return val;
}

double GetE (void)
{
    double val = GetT ();

    while (*s == '+' || *s == '-')
    {
        char op = *s;
        s++;

        double val2 = GetT ();

        if (op == '+')
            val += val2;
        else
            val -= val2;
    }

    return val;
}

double GetT (void)
{
    double val = GetP ();

    while (*s == '*' || *s == '/')
    {
        char op = *s;
        s++;

        double val2 = GetP ();

        if (op == '*')
            val *= val2;
        else
            val /= val2;
    }

    return val;
}

double GetP (void)
{
    if (*s == '(')
    {
        s++;
        double val = GetE ();
        Require (')');

        return val;
    }
    else
        return GetN ();
}

double GetN (void)
{
    double val = 0.0;
    const char *old_s = s;

    while ('0' <= *s && *s <= '9')
    {
        val = val*10 + (*s - '0');
        s++;
    }

    if (old_s == s)
        return NAN;

    return val;
}
