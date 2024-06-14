positive:
	mov byte [result], ' '
convert_to_ascii:
	add eax, '0'
	mov [result + 1], al
	mov eax, 4
	mov ebx, 1
	mov ecx, result
	mov edx, 3
	int 0x80
    mov eax, 1
	xor ebx, ebx
	int 0x80
section .data
	result db ' ', '0', 0xA
_start:
	mov eax, 7
	add eax, 3
	cmp eax, 0
	jge positive
	neg eax
	mov byte [result], '-'
	jmp convert_to_ascii
section .text
	global _start

