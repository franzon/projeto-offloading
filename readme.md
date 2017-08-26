# Exemplo básico Intel pin

Intercepta chamadas para a função printf.

## Para executar:

1. Compilar algum programa que use printf
2. `make`
3. Executar o programa de teste
4. `pin -pid *pid do processo de teste* -t obj-intel64/printftrace.so`

