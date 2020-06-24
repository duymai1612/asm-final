section .bss
    arr resb 1000
section .text
global decode_string
decode_string:
    push ebp
    mov ebp, esp

	; Reset dx
    xor edx, edx
    ; Move value of arg 1 dx
    mov dx, word[ebp+8]
	; Move value of arg 2 to cl
    mov cl, [ebp+12]

    ; Rotate dx
    rol dx, cl

    ; Copy decoded string to array
    mov byte[arr], dl
    mov byte[arr+1], dh

    ; Assign arr to eax to return
    xor eax, eax
    mov eax, arr
_exit_func:
	leave
	ret
