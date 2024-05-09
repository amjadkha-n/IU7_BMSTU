EXTRN input_digit_from_stdin:far
EXTRN print_str_to_stdout:far 
EXTRN print_digit_to_stdout:far
EXTRN print_char_to_stdout:far

STACKSEG SEGMENT PARA STACK 'STACK' 
    DB 300h dup('$')
STACKSEG ENDS 

DATASEG SEGMENT 'messages'
    mess_input_count_rows DB 10, 'Input count rows: ', '$'
    mess_input_count_cols DB 10, 'Input count columns: ', '$'
    mess_input_matrix DB 10, 'Input matrix:', 13, 10, '$'
    mess_result DB 10, 10, 'Result:', 13, 10, '$'
    mess_empty_res DB 10, 'Empty result', 10, '$' 
    mess_error_input_rows DB 10, 10, 'ERROR: invalid input count rows [int > 0 & < 10]', 10, '$' 
    mess_error_input_cols DB 10, 10, 'ERROR: invalid input count columns [int > 0 & < 10]', 10, '$' 
DATASEG ENDS 

DATASEG SEGMENT 'data' 
    count_rows DB ?  
    count_columns DB ?  
    matrix DB 9 * 9 dup (?) 
DATASEG ENDS   

DATASEG SEGMENT 'auxiliary_variables'
    found_elem DB ?
    ind_row DB ?   
DATASEG ENDS 

CODESEG SEGMENT PARA PUBLIC 'CODE'
    ASSUME CS:CODESEG, DS:DATASEG

error_input_count_rows: 
    lea bx, mess_error_input_rows
    call print_str_to_stdout

    mov ah, 4Ch 
    int 21h  
error_input_count_cols: 
    lea bx, mess_error_input_cols 
    call print_str_to_stdout

    mov ah, 4Ch 
    int 21h  

empty_res:
    lea bx, mess_empty_res
    call print_str_to_stdout 

    mov ah, 4Ch
    int 21h 

main: 
    mov ax, DATASEG 
    mov ds, ax 

    ; INPUT COUNT ROWS
	; In assembly language, the mov instruction is used to move data from one location to another, typically between registers or 
	; between a register and memory. On the other hand, the lea (load effective address) instruction is used to calculate the 
	; effective address of an operand and store it in a register, without actually loading any data from memory.
    lea bx, mess_input_count_rows 
    call print_str_to_stdout 

    call input_digit_from_stdin 
    mov count_rows, al 

    cmp count_rows, 0 
    je error_input_count_rows 

    ; INPUT COUNT COLUMNS
    lea bx, mess_input_count_cols
    call print_str_to_stdout 

    call input_digit_from_stdin 
    mov count_columns, al 

    cmp count_columns, 0 
    je error_input_count_cols

    ; INPUT MATRIX
    lea bx, mess_input_matrix  
    call print_str_to_stdout 

    mov ch, 0  
    mov si, 0 
    input_row: 
        mov bx, 0 
        mov cl, 0
        input_col: 
            mov ah, 1 
            int 21h

            mov matrix[si][bx], al     ; Store character in matrix
            inc bx

            mov ah, 2                  ; Print space
            mov dl, ' '
            int 21h

            inc cl   
            cmp cl, count_columns   
            jne input_col            

        mov ah, 2                
        mov dl, 10
        int 21h

        add si, 9                    

        inc ch                     
        cmp ch, count_rows           
        jne input_row                 

    cmp count_rows, 1         
    je empty_res                 

    ; SEARCH FOR ROW WITH EVEN NUMBER OF UNDERSCORES
    mov si, 0                         
    mov bx, 0                         
    mov al, matrix[si][bx]            
    mov found_elem, al                

    mov ch, 0                  

    find_row_with_even_US:        
        mov cl, 0                  
        mov al, 0                  
        mov found_elem, al           
        find_col_with_even_US:      
            mov al, matrix[si][bx]  
            cmp al, '_'    
            jne next      

            mov al, found_elem  
            inc al        
            mov found_elem, al  
            mov ind_row, ch 
        next:          
            inc bx     
            inc cl   
            cmp cl, count_columns 
            jne find_col_with_even_US 

        mov al, found_elem  
        cmp al, 0      
        je continue_loop  
        mov al, found_elem  
        test al, 1     
        jz _end     
    continue_loop:  
        mov bx, 0   
        add si, 9   

        inc ch             
        cmp ch, count_rows        
        jne find_row_with_even_US     

    mov al, count_rows             
    add al, 1                     
    mov count_rows, al             
    jmp _print  


_end:     

    ; mov bl, ind_row      
    ; call print_digit_to_stdout  

    ; DELETE COLUMN
    mov ch, 0                         ; Initialize ch for row counter
    mov bx, 0                         ; Initialize bx for column counter
    mov si, 0                         ; Initialize si for row index in original matrix
    mov di, 0                         ; Initialize di for row index in new matrix

    del_row:  
        cmp ind_row, ch       
        je next_row         

        mov cl, 0               
        mov bx, 0 

        del_col:   
            mov al, matrix[si][bx] 
            mov matrix[di][bx], al  

            inc bx  
            inc cl

            cmp cl, count_columns 
            jne del_col 

        add di, 9  
    next_row:  
        add si, 9  
        inc ch      
        cmp ch, count_rows            ; Compare row counter with count_rows
        jne del_row                   ; Jump back to del_row if not end of row

_print:
    ; PRINT MATRIX
    lea bx, mess_result         
    call print_str_to_stdout 
    mov ch, 0                           ; Initialize ch for row counter
    mov si, 0                           ; Initialize si for row index
    inc ch
    print_row: 
        mov bx, 0                        ; Initialize bx for column index
        mov cl, 0                        ; Initialize cl for column counter
        print_col:
            mov ah, 2         
            mov dl, matrix[si][bx] 
            int 21h 

            mov dl, ' '  
            int 21h 

            inc bx 

            inc cl  
            cmp cl, count_columns    
            jne print_col   

        add si, 9  

        mov ah, 2   
        mov dl, 10    
        int 21h     
        inc ch                            ; Increment ch for row counter
        cmp ch, count_rows               ; Compare ch with count_rows
        jne print_row                    ; Jump to print_row if not end of row

    mov ah, 4Ch 
    int 21h 
CODESEG ENDS                            ; End of code segment
END main                               ; End of program
