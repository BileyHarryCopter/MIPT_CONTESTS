#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define ZERO 0.00000000001

typedef double data_t;

typedef struct matrix
{
    data_t **row;
} matrix;

enum {
    FALSE = 0,
    TRUE
};

double mod (double val);
void data_to_int (data_t val);
void matr_print (matrix matr, unsigned N);
void matr_fill (matrix matr, unsigned N);
void matr_init (matrix *matr, unsigned N);
void matr_free (matrix *matr, unsigned N);
data_t matr_det (matrix matr, unsigned N);
int pivo_swap (matrix *matr, unsigned lead, unsigned N);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int main (void)
{
    matrix A   = {};
    unsigned N = 0;
    data_t det  = 0.0;

    scanf ("%d", &N);
    matr_init  (&A, N);
    matr_fill  (A, N);

    det = matr_det (A, N);
    data_to_int (det);

    matr_free (&A, N);
    return 0;
}
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
void matr_init (matrix *matr, unsigned N)
{
    unsigned i = 0;
    matr->row = (data_t **) calloc (N, sizeof (data_t *));
    for (i = 0; i < N; i++)
    {
        *(matr->row + i) = (data_t *) calloc (N, sizeof (data_t));
    }
}

void matr_fill (matrix matr, unsigned N)
{
    unsigned i, j = 0;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            scanf ("%lf", *(matr.row + i) + j);
        }
    }
}

void matr_print (matrix matr, unsigned N)
{
    unsigned i, j = 0;
    for (i = 0; i < N; i++)
    {
        printf ("\t");
        for (j = 0; j < N; j++)
        {
            printf ("%6lf\t", matr.row[i][j]);
        }
        printf ("\n");
    }
    printf ("\n\n");
}

void matr_free (matrix *matr, unsigned N)
{
    unsigned i = 0;
    for (i = 0; i < N; i++)
    {
        free (*(matr->row + i));
    }
    free (matr->row);
}

double mod (double val)
{
    if (val < 0)
        return -1.0*val;
    return val;
}

bool not_null (double val)
{
    if (mod(val) < ZERO)
        return FALSE;
    return TRUE;
}

void data_to_int (data_t val)
{
    if (val < 0)
    {
        val = -val;
        printf ("%d\n", -(int)(val + 0.5));
    }
    else
        printf ("%d\n", (int)(val + 0.5));
}

int pivo_swap (matrix *matr, unsigned lead, unsigned N)
{
    int i, j            = 0;
    int pivot_row       = lead;
    int pivot_col       = lead;
    int sign            = 1;
    data_t cur_pivot     = 0.0;
    data_t pivot         = matr->row[lead][lead];
    data_t *change_row   = NULL;

    // find out pivot element and his position in the matrix
    for (i = lead; i < N; i++)
    {
        for (j = lead; j < N; j++)
        {
            if (mod(pivot) < mod(matr->row[i][j]))
            {
                pivot     = matr->row[i][j];
                pivot_row = i;
                pivot_col = j;
            }
        }
    }
    if (not_null (pivot))
    {
        //  swap rows
        change_row = matr->row[lead];
        matr->row[lead] = matr->row[pivot_row];
        matr->row[pivot_row] = change_row;

        //  swap coloumns
        for (i = lead; i < N; i++)
        {
            cur_pivot = matr->row[i][pivot_col];
            matr->row[i][pivot_col] = matr->row[i][lead];
            matr->row[i][lead] = cur_pivot;
        }
        matr->row[lead][lead] = pivot;

        //  change sing of the determinant
        if (pivot_row != lead)
            sign *= -1;
        if (pivot_col != lead)
            sign *= -1;
    }

    return sign;
}

data_t matr_det (matrix matr, unsigned N)
{
    unsigned i, j, pos = 0;
    data_t first, main, koef = 0.0;
    data_t det = 1.0;
    int sign  = 1;

    for (i = 0; i < N; i++)
    {

        if (i == N - 1)
            break;

        sign *= pivo_swap (&matr, i, N);
        first = matr.row[i][i];
        if (not_null(first))
        {
            for (j = i + 1; j < N; j++)
            {
                main = matr.row[j][i];
                koef = main / first;
                for (pos = i; pos < N; pos++)
                {
                    matr.row[j][pos] -= koef * matr.row[i][pos];
                }
            }
        }
        else
            return 0;
    }

    for (i = 0; i < N; i++)
    {
        det *= matr.row[i][i];
    }


    return det * sign;
}
