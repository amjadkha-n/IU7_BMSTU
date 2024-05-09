;  Defines a data segment named "DATA" using the paragraph (16-byte) addressing scheme, marked as public.
SD1 SEGMENT para public 'DATA'
	; a byte variable named "S1" is declared within the data segment "SD1". The db directive is used to 
	; declare a byte (8 bits) variable. It's initialized with the ASCII character 'Y', so the variable "S1" will 
	; hold the ASCII value of 'Y', which is 89 in decimal and 59 in hexadecimal.
	S1 db 'Y'
	; This line allocates a block of memory within the data segment "SD1". It reserves a total of 65535 bytes (which is the maximum size 
	; of a paragraph in the 16-bit addressing scheme), and then subtracts 2 bytes because one byte is already reserved for the variable 
	; "S1". The dup directive is used to duplicate the value specified (in this case, 0) multiple times. So, this line effectively 
	; reserves 65533 bytes and initializes them all to zero.
	db 65535 - 2 dup (0)
SD1 ENDS
;  Defines another data segment named "DATA" using the paragraph (16-byte) addressing scheme, marked as public.
SD2 SEGMENT para public 'DATA'
	; Declares a byte variable S2 and initializes it with the ASCII character 'E'.
	S2 db 'E'
	; Allocates a block of 65533 bytes and initializes them to zero.
	db 65535 - 2 dup (0)
SD2 ENDS
; Defines another data segment named "DATA" using the paragraph (16-byte) addressing scheme, marked as public.
SD3 SEGMENT para public 'DATA'
	;  Declares a byte variable S3 and initializes it with the ASCII character 'S'.
	S3 db 'S'
	; Allocates a block of 65533 bytes and initializes them to zero.
	db 65535 - 2 dup (0)
SD3 ENDS
; Defines a code segment named "CODE" using the paragraph (16-byte) addressing scheme, marked as public.
CSEG SEGMENT para public 'CODE'
	; Specifies segment register assumptions. It assumes that the code segment (CS) is CSEG, and the data segment (DS) is SD1.
	assume CS:CSEG, DS:SD1
; Marks the beginning of the output procedure.
output:
	; Set the DOS function code for displaying a character (ah = 2) and generate a software 
	; interrupt (21h) to display the character in DL.
	mov ah, 2
	int 21h
	; Display a carriage return (ASCII 13).
	mov dl, 13
	int 21h
	;  Display a line feed (ASCII 10).
	mov dl, 10
	int 21h
	; Return from the output procedure.
	ret
; Marks the beginning of the main procedure.
main:
	; When we load the address of the data segment "SD1" into the AX register and set DS to that value, we're essentially
	;  telling the processor where to look for data when we reference variables within that segment. So, DS now points to
	;  the beginning of the "SD1" segment in memory.
	; Load the address of the data segment SD1 into the AX register and set the data segment register (DS) to that value.	
	mov ax, SD1
	; This line sets the data segment register (DS) to the value in the AX register. By setting DS to the address of "SD1", 
	; the processor knows to use "SD1" as the default segment for data operations.
	mov ds, ax
	; However, to actually access the value stored in the byte variable "S1" within the segment, we need to specify the offset within the 
	; segment where "S1" is located. In this case, "S1" is the first byte within the segment, so its offset is 0.
	;  Load the value of the byte variable S1 into the DL register and call the output procedure.
	; The DL register is one of the 8-bit general-purpose registers in the x86 architecture. It is 
	; commonly used for storing data, particularly single byte values
	mov dl, S1
	call output
; Specifies a change in the assumed data segment to SD2.
; Similar steps are repeated for SD2 and SD3, calling the output procedure for characters 'E' and 'S'.
assume DS:SD2
	mov ax, SD2
	mov ds, ax
	mov dl, S2
	; Calls the output procedure, passing the value stored in the DL register as an argument. This will display the character stored in S2.
	call output
assume DS:SD3
	mov ax, SD3
	mov ds, ax
	mov dl, S3
	call output
	; Set the exit code to 4c00h (indicating program termination) and generate a software interrupt (21h) to terminate the program.
	mov ax, 4c00h
	int 21h
CSEG ENDS
; Marks the end of the program, specifying the entry point as the "main" label.
END main


; This code defines three data segments (SD1, SD2, SD3) with byte variables S1, S2, and S3, each initialized with a single character ('Y', 'E', 'S').
; The code segment (CSEG) contains a procedure (output) for displaying characters on the screen using DOS interrupts.
; The main procedure calls the output procedure for each data segment, displaying characters 'Y', 'E', 'S' on the screen, and then terminates the program.