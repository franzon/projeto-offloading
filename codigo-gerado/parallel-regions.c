#include <stdio.h>
#include <omp.h>

int main()
{

    int i;
#pragma omp parallel private(i)
    {
#pragma omp for ordered
        for (i = 0; i < 100; i++)
            #pragma omp ordered
            printf("I: %d Thread: %d\n", i, omp_get_thread_num());
    }

    return 0;
}