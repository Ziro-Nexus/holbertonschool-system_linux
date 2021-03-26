BITS 64
	global asm_memcpy

	section .text
asm_memcpy:
	push rbp
	mov rbp, rsp
	push rdi
	xor rax, rax

do_while:
	test rdx, rdx
	jz end
	dec rdx
	mov al, BYTE [rsi]
	mov BYTE [rdi], al
	inc rdi
	inc rsi
	jmp do_while

end:
	pop rax
	mov rsp, rbp
	pop rbp
	ret
