BITS 64
	global asm_putc

	section .text
asm_putc:

	push rbp
	mov rbp, rsp

	sub rsp, 1
	mov [rsp], dil

	mov rax, 1
	mov rdi, 1
	mov rdx, 1
	mov rsi, rsp

	syscall

asm_putc_end:
	add rsp, 1
	mov rsp, rbp
	pop rbp	
	ret
