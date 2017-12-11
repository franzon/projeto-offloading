#include <stdio.h>

#pragma GCC push_options
#pragma GCC optimize("O0")
__attribute__((always_inline)) int __loop()

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

  __loop();
  for (int i = 0; i < 10; i++) {
    __loop();
    for (int j = 10; j > 0; j--)
      printf("%d ", j);
  }

  __loop();
  int x = 10;
  int y = 50;
  while (x < 20)
    x++;
}
