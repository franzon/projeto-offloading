#include <stdio.h>

#define Loop asm("nop \n\
        movl %eax, %eax \n\
        nop \n\
        movl %eax, %eax \n\
        nop \n\
");

int main()
{
    Loop;
    int i = 0;
    while (i < 10)
    {
        printf("Loop 1\n");
        i++;
    }

    Loop;
    for (int j = 50; j > 40; j--)
        printf("Loop 2\n");

    return 0;
}