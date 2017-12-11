	.file	"test.c"
	.intel_syntax noprefix
	.text
	.globl	loop_signature
	.type	loop_signature, @function
loop_signature:
.LFB2:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
#APP
# 9 "test.c" 1
	jmp 0f;
# 0 "" 2
# 10 "test.c" 1
	nop
# 0 "" 2
# 11 "test.c" 1
	mov %eax, %eax
# 0 "" 2
# 12 "test.c" 1
	mov %ebx, %ebx
# 0 "" 2
# 13 "test.c" 1
	nop
# 0 "" 2
# 14 "test.c" 1
	0:
# 0 "" 2
#NO_APP
	nop
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	loop_signature, .-loop_signature
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
#APP
# 9 "test.c" 1
	jmp 0f;
# 0 "" 2
# 10 "test.c" 1
	nop
# 0 "" 2
# 11 "test.c" 1
	mov %eax, %eax
# 0 "" 2
# 12 "test.c" 1
	mov %ebx, %ebx
# 0 "" 2
# 13 "test.c" 1
	nop
# 0 "" 2
# 14 "test.c" 1
	0:
# 0 "" 2
#NO_APP
	mov	DWORD PTR -4[rbp], 0
	jmp	.L3
.L4:
	mov	eax, DWORD PTR -4[rbp]
	mov	esi, eax
	lea	rdi, .LC0[rip]
	mov	eax, 0
	call	printf@PLT
	add	DWORD PTR -4[rbp], 1
.L3:
	cmp	DWORD PTR -4[rbp], 9
	jle	.L4
	mov	eax, 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Debian 7.2.0-16) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
