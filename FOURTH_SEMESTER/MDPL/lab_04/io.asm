PUBLIC input_digit_from_stdin
PUBLIC print_str_to_stdout
PUBLIC print_char_to_stdout
PUBLIC print_digit_to_stdout

CODESEG SEGMENT PARA PUBLIC 'CODE'
    ASSUME CS:CODESEG

print_str_to_stdout:
    mov ah, 9
    mov dx, bx
    int 21h
    ret

print_char_to_stdout:
    mov ah, 2
    mov dl, bl
    int 21h
    ret

input_digit_from_stdin:
    mov ah, 1
    int 21h
    sub al, 30h
    ret

print_digit_to_stdout:
    mov ah, 2
    add bl, 30h
    mov dl, bl
    int 21h
    ret

CODESEG ENDS
END
