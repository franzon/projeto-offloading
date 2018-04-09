#include <stdio.h>
#include <omp.h>

// Estava imprimindo resultados diferentes
// Resolvido com reduction

int main()
{
    int i = 0, j = 0;
#pragma omp parallel private(j) // tem diferença ser shared?
    {

#pragma omp for reduction(+ \
                          : i)
        for (j = 0; j < 100; j++)
            i += j;

#pragma omp master
        printf("Soma: %d\n", i);

#pragma omp barrier

#pragma omp for ordered
        for (i = 0; i < 10; i++)
#pragma omp ordered
            printf("i: %d [thread: %d]\n", i, omp_get_thread_num());
    }

        // Tesntando nowait. Perguntar para o rag
#pragma omp parallel
    {

#pragma omp for
        for (i = 0; i < 5; i++)
            printf("i = %d\n", i);
#pragma omp for
        for (i = 5; i < 10; i++)
            printf("i = %d\n", i);
    }

    return 0;
}