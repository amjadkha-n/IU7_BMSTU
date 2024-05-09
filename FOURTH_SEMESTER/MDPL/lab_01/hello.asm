.MODEL TINY
.DOSSEG
.DATA
    MSG DB "Hello, World!", 0Dh, 0Ah, '$'
.CODE
.STARTUP
    MOV AH, 09h        ; Selects the message display function
    MOV DX, OFFSET MSG ; Loads the message address into DX
    INT 21h            ; Calls the 21h interruption to display the message

    MOV AH, 4Ch       ; Selects the program output function
    INT 21h           ; Calls the 21h interruption to complete the program
END                 ; Indicates the end of the program
