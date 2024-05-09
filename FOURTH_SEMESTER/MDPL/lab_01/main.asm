; This directive specifies the memory model to be used for the program. 
; In this case, it's set to TINY, which is a simple memory model used for small programs.
.MODEL TINY
; This directive instructs the assembler to use DOS segment addressing. 
; It is often used in DOS programming to ensure proper segmentation.
.DOSSEG
; This section declares the data segment, where static data is defined.
.DATA
    ; This line declares a string named MSG with the value "Hello, World!" followed by 
    ; carriage return (moves the cursor to the beginning of the line without advancing to the next line and in ascii 
    ; it has a decimal value of 13 and This is a hexadecimal representation of the carriage return character ('\r'))(0Dh), 
    ; line feed (0Ah)(0Ah: This is a hexadecimal representation of the line feed character ('\n'). In ASCII, it has a 
    ; decimal value of 10. The line feed character is used to move the cursor to the next line.), 
    ; and a null-terminated character ('$'). The string is terminated with a dollar sign ('$').
    MSG DB "Hello, World!", 0Dh, 0Ah, '$'
; This section declares the code segment, where the executable instructions are placed.
.CODE
;  This is a predefined section that marks the beginning of the program execution.
.STARTUP
    ; This instruction moves the hexadecimal value 09h into the AH register. In DOS interrupt 21h, 
    ; AH often serves as a function code. In this case, 09h is used for displaying a string.
    MOV AH, 09h        ; Selects the message display function
    ;  This instruction moves the offset (memory address) of the MSG string into 
    ; the DX register. DX is often used to hold the address of data.
    MOV DX, OFFSET MSG ; Loads the message address into DX
    ; This instruction triggers a software interrupt 21h, which is a DOS interrupt. In this case, 
    ; it invokes the service specified by the value in the AH register (displaying the string).
    INT 21h            ; Calls the 21h interruption to display the message

    ; This instruction moves the hexadecimal value 4Ch into the AH register. In DOS interrupt 21h, 4Ch is used to terminate the program.
    ; he value 4Ch is the function code for program termination in DOS. 
    MOV AH, 4Ch       ; Selects the program output function
    ; This instruction again triggers a software interrupt 21h, invoking the service specified by 
    ; the value in the AH register (program termination).
    INT 21h           ; Calls the 21h interruption to complete the program
; Marks the end of the program.
END                 ; Indicates the end of the program
