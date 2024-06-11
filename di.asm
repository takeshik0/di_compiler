section .text
	global _start
_start:
	mov eax, 1
	sub eax, 3
	cmp eax, 0
	mov [result + 1], dl
	add eax, '0'
	jge positive
section .data
	result db '0', 0xA
	convert_to_ascii:
	mov eax, 4
	mov ebx, 1
	mov ecx, result
	mov edx, 2
	int 0x80
		mov eax, 1
	xor ebx, ebx
	int 0x80
	