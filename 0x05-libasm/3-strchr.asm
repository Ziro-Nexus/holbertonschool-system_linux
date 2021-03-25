BITS 64
	global asm_strchr
	section text
asm_strchr:
	push rbp
	mov rbp, rsp
	xor rax, rax

do:
	mov al, BYTE [rdi]
	cmp BYTE [rdi], sil
	jz find
	cmp BYTE [rdi], 0
	jz return
	inc rdi
	jmp do

find:
	mov rax, rdi

return:
	mov rsp, rbp
	pop rbp
	ret
