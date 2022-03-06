#include <stdio.h>
#include <stdlib.h>

float** matr_init (int N);
void matr_fill (int N, float **matr);
void matr_transform (int N, float **matr);
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
//===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*===*//
int main(void)
{
    int N, i = 0;
    float **matr = 0;
    scanf ("%d", &N);

    matr = matr_init (N);
    matr_fill (N, matr);

    matr_delete (N, matr);
    return 0;
}

int matr_init (int N)
{
    int i = 0;
    float **matr = (int **) calloc (N, sizeof (float *));
    for (i = 0; i < N; i++)
    {
        *(matr + i) = (float *) calloc (N, sizeof (float));
    }
    return matr;
}

void matr_fill (int N, float **matr)
{
    int i, j = 0;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            scanf ("%f", &matrix[i][j]);
        }
    }
}

void matr_GJ (int N, float **matr)
{
    int row, str, pos = 0;
    float lead_m, lead_p = 0.0;
    for (row = 0; row < N; row++)
    {
        lead_m = *((matr + row) + row)

        for (str = row + 1; str < N; str++)
        {
            lead_p = *(*(matr + str) + row);
            for (pos = str; pos < N; pos++)
            {
                *(*(matr + str) + pos) -= *(*(matr + row) + pos) * (lead_p / lead_m);
            }
        }
    }
}
