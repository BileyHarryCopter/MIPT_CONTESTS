#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define STRCAP 3

int matrdel (int ** matrix, int n)
{
    for (int i = 0; i < n; i++)
        free (matrix[i]);
    free (matrix);
    return 0;
}

int *compress (int ** matrix, int n, int m)
{
    assert (matrix);
    int * bigarray = (int *) calloc (STRCAP * n, sizeof (int)); //  создание главного массива
    int pos = 0;  //    инициализация бегунка по массиву

    //  проход по матрице в следующем порядке:
    //  заходим в i-ю строку и проверяем все элементы (от нулевого до m-1-го) в ней
    //  делаем проверку на ненулевые элементы, если их количество не равно 3 - выдаем ошибку
    //  после проверки идем в i+1-ю строку

    for (int i = 0; i < n; i++)
    {
        int positive = 0;
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] > 0)
            {
                bigarray [pos] = matrix[i][j];
                pos++;
                positive++;
            }
        }
        if (positive != 3)
        {
            matrdel (matrix, n);
            free (bigarray);
            return NULL;
        }
    }

    //  освобждение памяти под матрицу
    matrdel (matrix, n);

    return bigarray;
}

void matrprint (int ** matrix, int n, int m)
{
    assert (matrix);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf ("%d ", matrix[i][j]);
        }
        printf ("\n");
    }
}

void arrayprint (int * array, int n)
{
    assert (array);
    for (int i = 0; i < n * STRCAP; i++)
    {
        printf ("%d ", array[i]);
    }
    printf ("\n");
}

int main (void)
{
    int n, m = 0;

    scanf ("%d %d", &n, &m);

    //  инициализация матрицы
    int ** matrix = (int **) calloc (n, sizeof (int *));
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (int *) calloc (m, sizeof (int));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            scanf ("%d", &matrix[i][j]);
    }

    matrprint (matrix, n, m);
    int * array = compress (matrix, n, m);

    arrayprint (array, m);
    free (array);

    return 0;
}
