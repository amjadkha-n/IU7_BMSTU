
public min_degree_two
extrn num: word


DATASEG SEGMENT PARA PUBLIC 'DATA'
    out_msg db 'Minimum degree of two exceeding entered number: $'
    result_buffer db 6 dup ('$') 
DATASEG ENDS

CODESEG SEGMENT PARA PUBLIC 'CODE'
    assume CS:CODESEG, DS:DATASEG 

min_degree_two proc near
    mov ax, DATASEG
    mov ds, ax

    mov bx, num  ; 
    mov ax, 1  ; Initialize AX to 1 (minimum power of 2)
    mov cx, 0  ; Initialize a counter to keep track of the power of 2

next_power:
    shl ax, 1
    inc cx

    cmp ax, bx 
    jg print_result
    jmp next_power

print_result:
    ; Convert the power of 2 to ASCII and store it in the buffer
    mov di, OFFSET result_buffer + 5
    mov byte ptr [di], '$'

    ; Convert the power of 2 (counter) to ASCII and store it in the buffer
    mov bx, 10  ; Load the divisor (10) into BX
    mov ax, cx  ; Move the counter value (power of 2) into AX

convert_loop:
    dec di  
    xor dx, dx
    div bx
    add dl, '0'
    mov [di], dl
    test ax, ax 
    jnz convert_loop

    ; Print the result
    mov dx, OFFSET out_msg
    mov ah, 9  ; Set the function number for 'print string' in AH
    int 21h

    mov dx, di
    mov ah, 9 
    int 21h  

    ret 

min_degree_two endp
CODESEG ENDS
END