section .text
	global _start
_start:
	mov edx, 0
	mov ecx, result
	mov ebx, 1
	mov eax, 4
	int 0x80
mov eax, 1
	int 0x80
section .data
	result db '', 0xA
