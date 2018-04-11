#include <stdio.h>
#include <omp.h>

int main()
{

    int i = 10, k = 5;
#pragma omp parallel private(i) firstprivate(k)
    {
        printf("Executado por todas as threads. [%d]\n", omp_get_thread_num());

#pragma omp single
        {
            printf("Executado por uma única thread. [%d]\n", omp_get_thread_num());
        }
#pragma omp critical
        {
            printf("Executado por uma thread de cada vez. [%d]\n", omp_get_thread_num());
        }

#pragma omp barrier

#pragma omp single
        printf("Espera todas as threads terminarem a execução\n");

        printf("Executado por todas as threads. [%d]\n", omp_get_thread_num());

        printf("Valor de i: %d\n", i);
        printf("Valor de k: %d\n", k);

        i = 100;
        k = 200;
    }

    printf("[Fora do parellel] Valor de i: %d\n", i);
    printf("[Fora do parellel] Valor de k: %d\n", k);

    return 0;
}