section .text
	global _start
section .bss
	buffer resb 12
section .data
	result db ' ', '0', 0xA
_start:
	mov eax, 1000
	sub eax, 7
	add eax, 12
	sub eax, 5
	cmp eax, 0
	jge positive
	neg eax
	mov byte [result], '-'
	jmp convert_loop
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
	mov ecx, result
	mov edx, 1
	int 0x80
print_number:
	mov eax, 4
	mov ebx, 1
	int 0x80
	mov eax, 1
	xor ebx, ebx
	int 0x80
