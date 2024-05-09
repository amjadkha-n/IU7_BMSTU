; Define a stack segment named 'stgSeg' with paragraph size, allocating 512 bytes of stack space
stgSeg  SEGMENT PARA STACK 'STACK'
        Db 200h DUP (?)
stgSeg  ENDS 

; Define a data segment named 'dataS' with word alignment
;  This directive reserves 512 bytes (200h in hexadecimal) within the stack 
; segment and initializes each byte with a question mark (?). The question mark is often used as a placeholder or uninitialized value.
dataS   SEGMENT WORD 'DATA'
    ; Define a string 'HelloMessage' with carriage return, line feed, 'Hello, world!', and a null terminator
    HelloMessage    DB 13
                    DB 10
                    DB 'Hello, world!'
                    DB '$'
DataS   ENDS

; Define a code segment named 'Code' with word alignment and assume CS points to 'Code' and DS points to 'DataS'
Code    SEGMENT WORD 'CODE'
        ASSUME CS:CODE, DS:DataS

DispMsg:
        mov AX,DataS                    ; Load the address of the data segment into AX
        mov DS,AX                       ; Set DS to the loaded address (DS points to 'DataS')
        mov CX, 3                       ; Commented out, likely intended for loop control

    DisplayLoop:
        mov DX,OFFSET HelloMessage      ; Load the offset of 'HelloMessage' into DX
        mov AH,9                        ; Set AH to 09h for DOS display string function
        int 21h                         ; Call DOS function to display the string
        loop DisplayLoop                ; Commented out loop instruction

        mov AH,7                        ; Set AH to 07h for DOS input without echo function
        INT 21h                         ; Call DOS function to input a character without echo
        mov AH,4Ch                      ; Set AH to 4Ch for DOS terminate process function
        int 21h                         ; Call DOS function to terminate the process

Code    ENDS
        END DispMsg                     ; End of the program
