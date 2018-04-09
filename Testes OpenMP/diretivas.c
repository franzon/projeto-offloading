#include <stdio.h>
#include <omp.h>

int main()
{

#pragma omp parallel
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
    }

    return 0;
}