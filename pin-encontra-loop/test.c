#include <stdio.h>

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
