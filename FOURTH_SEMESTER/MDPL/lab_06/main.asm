.MODEL TINY
.CODE
.386

ORG 100h 

MAIN:
    TIME DB 0
    MOV AH, 02h
    INT 1Ah
    MOV TIME, DH
	
    SPEED DB 01Fh
    OLD_08H DD ?
    IS_INIT DB 'I'

    JMP INIT

INT_08h_HANDLER PROC NEAR
    PUSHA
    ;PUSHF
    PUSH ES
    PUSH DS

    MOV AH, 02h
    INT 1Ah ;Count the time from the constant real-time clock. The seconds will be in DH

    CMP DH, TIME
    MOV TIME, DH
    JE QUIT

    MOV AL, 0F3h ;Keyboard command to adjust the auto-repeat speed
    OUT 60h, AL
    MOV AL, SPEED ;Speed change
    OUT 60h, AL

    DEC SPEED
    DEC SPEED
    DEC SPEED
    DEC SPEED
    DEC SPEED
    
    JNZ QUIT
    MOV SPEED, 01fh ;Cycling the speed in a circle

    QUIT:
        POP DS
	    POP ES
	    ;POPF
	    POPA

        JMP CS:OLD_08H
; какая комманда завершает обработку программа?
; iret

INT_08h_HANDLER ENDP

INIT:
    MOV AX, 3508h ;Getting the address of the interrupt vector handler (in ES:BX)
    INT 21H

    CMP ES:IS_INIT, 'I'
    JE UNINSTALL

    MOV WORD PTR OLD_08H, BX ;Saving the handler's address
    MOV WORD PTR OLD_08H + 2, ES

    MOV AX, 2508h ; Setting the interrupt vector. DS:DX = interrupt vector: address of the interrupt processing program
    MOV DX, OFFSET INT_08h_HANDLER ;address of the termination processing program
    INT 21H

    MOV DX, OFFSET INIT ;The address of the last byte of the resident program
    INT 27H ;Resident completion

UNINSTALL:
    PUSH ES
    PUSH DS

    ;Setting the old interrupt vector
    MOV DX, WORD PTR ES:OLD_08H
    MOV DS, WORD PTR ES:OLD_08H + 2
    MOV AX, 2508h 
    INT 21H
  
    POP DS
    POP ES
    MOV AH, 49h ;Freeing up a distributed memory block
    INT 21h

    MOV AX, 4C00h ;Completion of the program
    INT 21h
    
END MAIN
