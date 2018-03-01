# encontra loops com a seguinte marcação:

```
nop
mov eax, eax
nop
mov eax, eax
nop
```

Está funcionando para loops básicos compilados com GCC.
Testei com o clang e não funcionou, parece que ele usa uma lógica diferente para gerar os loops.