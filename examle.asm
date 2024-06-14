section .data
	result db ' ', '0', 0xA
section .bss
    buffer resb 12
section .text
	global _start
_start:	
	mov eax, 90
	add eax, 11
	cmp eax, 0
	jge positive
	neg eax
	mov byte [result], '-'
	;jmp convert_to_ascii
positive:
	mov edi, buffer + 12
	mov ebx, 10
convert_loop:
	xor edx, edx        ; Clear edx before dividing (EDX:EAX is used by DIV)
    div ebx             ; Divide EAX by 10, quotient in EAX, remainder in EDX
    add dl, '0'         ; Convert remainder to ASCII
    dec edi             ; Move buffer pointer backward
    mov [edi], dl       ; Store ASCII character at buffer
    test eax, eax       ; Check if quotient is 0
    jnz convert_loop    ; If not zero, repeat the loop

	mov eax, buffer + 12 ; End of buffer
    sub eax, edi        ; Length of number string
    mov edx, eax ; Calculate the length of the number string

	mov ecx, edi

    ; Print the sign if it's negative
    cmp byte [result], '-'
    jne print_number

    ; Print the negative sign
    mov eax, 4
    mov ebx, 1
    mov ecx, result
    mov edx, 1
    int 0x80

print_number:
    ; Print the number
    mov eax, 4
    mov ebx, 1
    int 0x80

    ; Exit
    mov eax, 1
    xor ebx, ebx
    int 0x80

