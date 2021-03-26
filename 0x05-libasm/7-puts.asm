BITS 64
	global asm_puts		; export 'asm_puts' function
	extern asm_strlen	; import 'asm_strlen' function
	section .text


asm_puts:
	push rbp
	mov rbp, rsp
	sub rsp, 12
	mov [rsp], rdi
	call asm_strlen	
	mov [rsp - 8], eax
	mov rax, 1
	mov rdi, 1
	mov edx, [rsp - 8]
	mov rsi, [rsp]
	syscall	

asm_puts_end:
	add rsp, 12	
	mov rsp, rbp
	pop rbp	
	ret	
