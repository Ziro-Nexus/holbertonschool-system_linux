BITS 64
	global asm_strcmp

	section .text

asm_strcmp:
		movsx   edx, byte [rdi]
		test    dl, dl
		jz      func3
		movsx   ecx, byte [rsi]
		xor     eax, eax
		cmp     dl, cl
		jz      func2
		jmp     func4

func1:  add     rax, 1
		movsx   ecx, byte [rsi+rax]
		cmp     dl, cl
		jnz     func4
func2:  movsx   edx, byte [rdi+rax+1H]
		test    dl, dl
		jnz     func1
func3:  xor     eax, eax
		ret

func4:  sub     edx, ecx
		xor     eax, eax
		test    edx, edx
		setg    al
		lea     eax, [rax+rax-1H]
		ret
