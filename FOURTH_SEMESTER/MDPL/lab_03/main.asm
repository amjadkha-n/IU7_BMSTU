EXTERN print_z: far 

SSTK SEGMENT para STACK 'STACK'
	db 100 dup(0) 
SSTK ENDS

USER_DATA SEGMENT para public 'DATA'
    buffer db 2 
USER_DATA ENDS

SC1 SEGMENT para public 'CODE'
	assume CS:SC1, DS:USER_DATA 
main:
    mov AX, USER_DATA
    mov DS, AX

    ;0Ah- Мин. выделение памяти в параграфах
    ; Here, AH = 0Ah specifies that it's a buffered input function. 
    MOV AH, 0Ah
    ; The offset address represents the distance of the variable or label from the beginning of its segment.
    MOV DX, offset buffer
    INT 21h	
    SUB buffer + 2, '0'
    mov CL, buffer + 2

    jmp print_z
SC1 ENDS
END main ; The entry point to the program.
