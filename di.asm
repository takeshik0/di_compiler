section .text
	global _start
_start:
	mov eax, 2
	imul eax, 3
	add eax, 2
	cmp eax, 0
	jge positive
	neg eax
	mov byte [result], '-'
	jmp convert_loop
section .bss
	buffer resb 12
section .data
	result db ' ', '0', 0xA
positive:
	mov edi, buffer + 12
	mov ebx, 10
convert_loop:
	xor edx, edx
	div ebx
	add dl, '0'
	dec edi
	mov [edi], dl
	test eax, eax
	jnz convert_loop
	mov eax, buffer + 12
	sub eax, edi
	mov edx, eax
	mov ecx, edi
	cmp byte [result], '-'
	jne print_number
	mov eax, 4
	mov ebx, 1
	lea ecx, [result]
	mov edx, 1
	int 0x80
print_number:
	mov eax, 4
	mov ebx, 1
	int 0x80
	mov eax, 1
	xor ebx, ebx
	int 0x80
