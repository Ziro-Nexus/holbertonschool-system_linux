BITS 64
	global asm_puti		; export 'asm_puti' function

	extern asm_putc		; import 'asm_putc' function

	section .text

asm_puti:

	push rbp
	mov rbp, rsp
	sub rsp, 20

asm_puti_rax:

	mov qword [rsp - 12], 0 ; save return value on the stack

asm_puti_n:

	mov [rsp - 8], edi	; copy @n onto the stack

asm_puti_sign:

	mov dword [rsp - 4], 1	; copy 1 onto the stack

	cmp edi, 0		; compare 0 with @n

	jge asm_puti_char	; jump to "char" if @n is non-negative

	neg dword [rsp - 4]	; flip the sign

asm_puti_char:

	mov dword [rsp], 0x30
	xor edx, edx
	mov eax, edi
	mov edi, 10
	idiv edi
	mov eax, edx
	imul dword [rsp - 4]
	add [rsp], eax

asm_puti_loop:

	cmp dword [rsp - 8], 0
	jge asm_puti_loop_div
	mov edi, 0x2D
	call asm_putc
	inc qword [rsp - 12]

asm_puti_loop_div:
	xor edx, edx
	mov eax, [rsp - 8]
	mov edi, 10
	idiv edi
	cmp eax, 0
	je asm_puti_loop_putc
	imul dword [rsp - 4]
	mov edi, eax
	call asm_puti
	add [rsp - 12], rax

asm_puti_loop_putc:

	mov edi, [rsp]
	call asm_putc
	inc qword [rsp - 12]

asm_puti_end:

	mov rax, [rsp - 12]
	add rsp, 20
	mov rsp, rbp
	pop rbp
	ret
