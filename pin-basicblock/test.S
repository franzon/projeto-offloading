	.file	"test.c"
	.intel_syntax noprefix
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	DWORD PTR -4[rbp], 0
	jmp	.L2
.L7:
	mov	DWORD PTR -8[rbp], 5
	jmp	.L3
.L6:
	mov	edi, 88
	call	putchar@PLT
	mov	DWORD PTR -12[rbp], 0
	jmp	.L4
.L5:
	mov	edi, 121
	call	putchar@PLT
	add	DWORD PTR -12[rbp], 1
.L4:
	cmp	DWORD PTR -12[rbp], 1
	jle	.L5
	add	DWORD PTR -8[rbp], 1
.L3:
	cmp	DWORD PTR -8[rbp], 14
	jle	.L6
	add	DWORD PTR -4[rbp], 1
.L2:
	cmp	DWORD PTR -4[rbp], 9
	jle	.L7
	mov	eax, 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Debian 6.3.0-18) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
