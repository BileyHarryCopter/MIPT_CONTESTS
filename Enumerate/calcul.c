#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

typedef struct string_t
{
    char    *data;
    unsigned  pos;
} string_t;


double parce_str (string_t *StrinG);
double parce_expr (string_t *StrinG);
double parce_mult (string_t *StrinG);
double parce_brac (string_t *StrinG);
double parce_numb (string_t *StrinG);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int main (void)
{
    string_t StrinG = {"(2-421)$", 0};
    double ans = parce_str (&StrinG);

    if (ans != ans)
    {
        printf ("SYNTAX ERROR\n");
        return 0;
    }
    printf ("ANSWER : %.2lf\n", ans);
	return 0;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
double parce_str (string_t *StrinG)
{
    printf ("in %s : %c\n", __PRETTY_FUNCTION__, StrinG->data[StrinG->pos]);
    double value = parce_expr (StrinG);

    if (StrinG->data[StrinG->pos] != '$')
        return NAN;

    return value;
}

double parce_expr (string_t *StrinG)
{
    printf ("in %s : %c\n", __PRETTY_FUNCTION__, StrinG->data[StrinG->pos]);
    double value_1 = parce_mult (StrinG);

    while (StrinG->data[StrinG->pos] == '+' || StrinG->data[StrinG->pos] == '-')
    {
        char op = StrinG->data[StrinG->pos];

        StrinG->pos++;
        double value_2 = parce_mult (StrinG);

        if (op == '+')
            value_1 += value_2;
        else if (op == '-')
            value_1 -= value_2;
    }
    return value_1;
}

double parce_mult (string_t *StrinG)
{
    printf ("in %s : %c\n", __PRETTY_FUNCTION__, StrinG->data[StrinG->pos]);
    double value_1 = parce_brac (StrinG);

    while (StrinG->data[StrinG->pos] == '*' || StrinG->data[StrinG->pos] == '/')
    {
        char op = StrinG->data[StrinG->pos];

        StrinG->pos++;
        double value_2 = parce_brac (StrinG);

        if (op == '*')
            value_1 *= value_2;
        else if (op == '/')
            value_1 = (double) value_1 / value_2;
    }
    return value_1;
}

double parce_brac (string_t *StrinG)
{
    printf ("in %s : %c\n", __PRETTY_FUNCTION__, StrinG->data[StrinG->pos]);
    if (StrinG->data[StrinG->pos] == '(')
    {
        StrinG->pos++;
        double value = parce_expr (StrinG);
        if (StrinG->data[StrinG->pos] != ')')
            return NAN;
        StrinG->pos++;
        return value;
    }
    else
        return parce_numb (StrinG);
}

double parce_numb (string_t *StrinG)
{
    printf ("in %s : %c\n", __PRETTY_FUNCTION__, StrinG->data[StrinG->pos]);
    int length   = 0;
    char digit   = StrinG->data[StrinG->pos];
    double value = 0.0;
    while (isdigit (digit))
    {
        value = 10*value + (digit - '0');
        StrinG->pos++;
        digit = StrinG->data[StrinG->pos];
        length++;
    }
    if (length == 0)
        return NAN;
    return value;
}
