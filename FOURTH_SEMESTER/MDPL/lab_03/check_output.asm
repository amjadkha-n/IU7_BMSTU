PUBLIC print_z

DATA_PRINT SEGMENT para public 'DATA'
    symb    db "Z", 13, 10, '$'  ; Adding carriage return (CR) and line feed (LF) characters after "A"
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

    ; Removing the lines mov AX, 4c00h and int 21h from the code will cause the program not to properly terminate. This means 
    ; it might keep running indefinitely, causing potential issues such as freezing or system instability. These 
    ; lines are crucial for telling the operating system that the program has finished its execution.
    ; Completion of the program.
    mov AX, 4c00h
	int 21h
SC2 ENDS
END
