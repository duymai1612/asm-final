section .text
global encode_string
encode_string:
    push ebp
    mov ebp, esp

    ; Move address of arg 1 to eax
    mov eax, [ebp+8]
    ; Move value of arg 2 to cl
    mov cl, [ebp+12]
    
	; Reset dx
    xor edx, edx
	; Move 2 chars at address stored in eax to dx
    mov dx, word[eax]

    ; Rotate dx
    ror dx, cl

    ; Return
    xor eax, eax
    mov ax, dx

_exit_function:
	leave
	ret
