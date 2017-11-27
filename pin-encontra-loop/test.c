#include <stdio.h>
#include <stdlib.h>


#pragma GCC push_options
#pragma GCC optimize ("O0")
__attribute__((always_inline)) void loop_signature()
{
    asm volatile("jmp 0f;");
    asm volatile("nop");
    asm volatile("mov %eax, %eax");
    asm volatile("mov %ebx, %ebx");
    asm volatile("nop");
  asm volatile("0:");
}
#pragma GCC pop_options


int main()
{
    loop_signature();
    for (int i = 0; i < 10; ++i)
    {
        printf("%d\n", i);
    }
    return 0;
}
