; Указываем, что идентификатор
; определен в другом модуле.
; По заданию:
; Дальний (far) - на произвольный адрес.
EXTERN print_a: far 

; Объявляем сегмент со смещением, кратному параграфу (16 байт) для стека.
SSTK SEGMENT para STACK 'STACK'
	db 100 dup(0) ; duplicate (Инициализируем нулями).
SSTK ENDS

; Объявляем сегмент, в который запишем данные (цифру)
; Которую введет пользователь
USER_DATA SEGMENT para public 'DATA'
    ; Т.к. по заданию цифра. (Дальше понадобится)(цифра + enter).
    buffer db 2 
USER_DATA ENDS

; Сегмент кода.
SC1 SEGMENT para public 'CODE'
    ; Контролируем правильное обращение к переменным.
	assume CS:SC1, DS:USER_DATA 
main:
    ; Кладем в DS данные.
    mov AX, USER_DATA
    mov DS, AX
    ; This sets the value of the AH register to 0Ah, which is a function code indicating buffered input operation. This means 
    ; the program is going to read input from the keyboard with buffering enabled.
    ; Послыаем в AH код, которы будет ожидать 
    ; ввода с клавиатуры (STDIN) и запишет в буфер.
    ; DS:DX - адрес буфера.
    ; На выходе буфер будет содержать строку.
    ; Также нужно подготовить буфер, для этого 
    ; В буфере первый байт должен содержать число, которое
    ; определяет максимальное число символов для ввода.
    ; В нашем случае мы изначально инициализируемю числом два(цифра + enter).
    MOV AH, 0Ah
    MOV DX, offset buffer
    INT 21h	

    ; Строка запишется в буфер, начиная с третьего байта.
    ; Во втором будет длина реально введеной строки.
    ; Поэтому, чтобы установить счетчик нам нужно сместиться на 2.
    ; Также чтобы преобразовать символ, введеный с клавиатуры, из 
    ; ASCII в цифру, нам нужно вычесть 30h.
    SUB buffer + 2, '0'
    mov CL, buffer + 2

    ; Безусловный переход на метку print_a.
    jmp print_a
SC1 ENDS
END main ; Точка входа в программу.




; In assembly language, the term "offset" typically refers to the distance between the beginning of a section of memory and a 
; specific location within that section. It is often used in conjunction with memory addresses to access specific data or instructions.