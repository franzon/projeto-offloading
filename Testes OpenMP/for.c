#include <stdio.h>
#include <omp.h>

// Estava imprimindo resultados diferentes
// Resolvido com reduction

int main()
{
    int i = 0, j = 0;
#pragma omp parallel private(j) // o j poderia ser shared?
    {

#pragma omp for reduction(+ \
                          : i)
        for (j = 0; j < 100; j++)
            i += j;

#pragma omp master // só é executado pela thread principal
        printf("Soma: %d\n", i);

#pragma omp barrier // espera executar todas as threads

#pragma omp for ordered
        for (i = 0; i < 10; i++)
#pragma omp ordered
            printf("i: %d [thread: %d]\n", i, omp_get_thread_num());
    }

        // Testando nowait. Por que sem o nowait cada for é executado sequencialmente?
#pragma omp parallel
    {

#pragma omp for //nowait
        for (i = 0; i < 5; i++)
            printf("A [thread: %d] i = %d\n", omp_get_thread_num(), i);
#pragma omp for //nowait
        for (i = 5; i < 10; i++)
            printf("B [thread: %d] i = %d\n", omp_get_thread_num(), i);
    }

    return 0;
}