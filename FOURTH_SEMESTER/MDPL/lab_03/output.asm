PUBLIC print_z

DATA_PRINT SEGMENT para public 'DATA'
    symb    db "Z", 13, 10, '$'
DATA_PRINT ENDS

SC2 SEGMENT para public 'CODE'
    assume  CS:SC2, DS:DATA_PRINT
print_z:
    mov AX, DATA_PRINT
    mov DS, ax

    ; 09h - Write a string to STDOUT.
    ; DS:DX - the address of the string ending with the character "$".
    MOV DX, offset symb
    ; 09h is a DOS function code indicating that the programmer wants to print a string to the standard output (console).
    MOV AH, 09h

print:
    int 21h
    LOOP print

    mov AX, 4c00h
	int 21h
SC2 ENDS
END
