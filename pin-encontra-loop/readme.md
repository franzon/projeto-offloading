# pin tool para encontrar loops

Procura por saltos para um endereço anterior ao da instrução. (prováveis loops).

## Para testar:
1. ```make```
2. ```gcc test.c -o test.out```
3. ```pin -t obj-intel64/loop.so -- ./test.out```

## Programa de teste:

```
int main()
{

	for (int i = 0; i < 10; i++)
	{
		printf("X");
	}

	return 0;
}
```

Saída após executar o pin:

```
55622fff96b0 : push rbp
55622fff96b1 : mov rbp, rsp
55622fff96b4 : sub rsp, 0x10
55622fff96b8 : mov dword ptr [rbp-0x4], 0x0
55622fff96bf : jmp 0x55622fff96cf
 55622fff96c1 : mov edi, 0x58
 55622fff96c6 : call 0x55622fff9560
 55622fff96cb : add dword ptr [rbp-0x4], 0x1
 55622fff96cf : cmp dword ptr [rbp-0x4], 0x9
 55622fff96d3 : jle 0x55622fff96c1 -- HERE -- Target: 55622fff96c1
55622fff96d5 : mov eax, 0x0
55622fff96da : leave 
55622fff96db : ret 
```

Então professor, agora estou com dúvida a partir de qual instrução do loop eu devo extrair para reconstruir o código LLVM...
No exemplo de cima, seria do endereço **55622fff96c1** até o **55622fff96d3**?
Isso seria suficiente para reconstruir o código ou preciso de algumas instruções anteriores?


