#include <stdio.h>
#include <omp.h>

#define MAX_COL 4

void matrix_mult(int matA[][MAX_COL], int matB[][MAX_COL], int matC[][MAX_COL], int lines, int cols)
{
    int i, j, k, sum;
    #pragma omp parallel private(j) // perguntar para o rag
    {
        #pragma omp for
        for (i = 0; i < lines; i++)
        {
            for (j = 0; j < cols; j++)
            {
                printf("[Thread: %d] i = %d j = %d k = %d\n", omp_get_thread_num(), i, j, k);
                sum = 0;
                for (k = 0; k < lines; k++)
                {
                    sum += (matA[i][k] * matB[k][j]);
                }
                matC[i][j] = sum;
            }
        }
    }
}

int main()
{

    int matA[][MAX_COL] = {{1, 2, 3, 4}, {4, 5, 6, 7}, {7, 8, 9, 10}, {100, 200, 300, 400}};
    int matB[][MAX_COL] = {{1, 11, 12, 13}, {2, 14, 15, 16}, {3, 17, 18, 19}, {7, 7, 7, 7}};
    int matC[4][MAX_COL];
    matrix_mult(matA, matB, matC, 4, 4);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", matC[i][j]);
        }
        printf("\n");
    }

    return 0;
}