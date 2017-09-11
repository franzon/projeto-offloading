# Teste basic block

Conta a quantidade de "traces" e "basic blocks".

*Traces são blocos de instruções com uma entrada e uma saída incondicional.
*Basic blocks são blocos de instruções com uma entrada e uma saída condicional.
*Um Trace pode conter vários Basic blocks.

## Para executar:
1. make
2. gcc test.c -o test.out
3. pin -t obj-intel64/bb.so -- ./test.out 




