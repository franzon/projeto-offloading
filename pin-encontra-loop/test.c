#include <stdio.h>

<<<<<<< HEAD
#pragma GCC push_options
#pragma GCC optimize("O0")
__attribute__((always_inline)) int loop()

{
  asm("nop \n\
      movl %eax, %eax \n\
        nop \n\
        movl %eax, %eax \n\
        nop \n\
");
}
#pragma GCC pop_options

int main() {

  loop();
  for (int i = 0; i < 10; i++)
    printf("%d ", i);
}
=======

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
>>>>>>> e065af4c7e2ec60a785e591c5ec2692384123ce0
