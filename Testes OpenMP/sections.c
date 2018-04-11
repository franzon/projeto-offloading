#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp sections
    {
#pragma omp section
        {
            printf("Teste 1\n");
            printf("Teste 2\n");
        }

#pragma omp section
        printf("Teste 3\n");

        //#pragma omp section
    }
    return 0;
}