bits 64
global main
%define GTK_WIN_POS_CENTER 1
%define GTK_WIN_WIDTH 750
%define GTK_WIN_HEIGHT 150
%define GTK_ORIENTATION_HORIZONTAL 1
%define LAYOUT_BOX_SPACING 10
%define ENTRY_SIZE 1024
extern get_root
extern exit
    extern get_root
;For the location of objects
    extern gtk_box_new
; To create a button
    extern gtk_container_add
    extern gtk_button_new_with_label
; To create input/output fields
    extern gtk_entry_buffer_new
    extern gtk_entry_get_text
    extern gtk_entry_new_with_buffer
    extern gtk_entry_set_placeholder_text
    extern gtk_label_new
    extern gtk_label_set_text
; To work with text
    extern sprintf
    extern sscanf
    extern gtk_entry_set_text
; To work with window
    extern gtk_init
    extern gtk_main
    extern g_object_set
    extern gtk_main_quit
    extern gtk_window_new
    extern gtk_widget_show_all
    extern g_signal_connect
    extern gtk_window_set_title
    extern g_signal_connect_data
    extern gtk_window_set_position
    extern gtk_settings_get_default
    extern gtk_widget_set_size_request
    extern gtk_window_set_default_size
    extern gtk_message_dialog_new
    extern gtk_dialog_run
    extern gtk_widget_destroy
section .data
    result_text_buffer          db ENTRY_SIZE dup (0)
    title                       db "y=cos(x^3 + 7)", 0
    solve_button_title          db "Find root", 0

    start_x_placeholder_text    db "Enter a", 0
    end_x_placeholder_text      db "Enter b", 0
    iters_num_placeholder_text  db "Iters", 0
    result_placeholder_text     db "Result", 0

    result_format               db "%lf", 0
    x_format                    db "%lf", 0
    iters_num_format            db "%d", 0

    float_start                 dq 0
    float_end                   dq 0
    int_iters_num               dq 0

section .bss
    window:             resq 1
    layout_box:         resq 1

    solve_button:       resq 1
    start_x_entry:      resq 1
    end_x_entry:        resq 1
    iters_num_entry:    resq 1 
    result_label:       resq 1 
    message_dialog:     resq 1

    
    start_x_buffer:     resq 1 
    end_x_buffer:       resq 1 
    iters_num_buffer:   resq 1
section .rodata
    signal:
    .destroy: db "destroy", 0
    .clicked: db "clicked", 0
section .text
    _destroy_window:
    jmp gtk_main_quit

solve_command:
    push rbp
    mov rbp, rsp
    mov rdi, qword [rel end_x_entry]
    call gtk_entry_get_text
    mov rdi, rax
    mov rbx, rax
    mov rsi, result_format
    mov rdx, float_end
    call sscanf
    pop rbp
       
    push rbp
    mov rbp, rsp
    mov rdi, qword [rel start_x_entry]
    call gtk_entry_get_text
    mov rdi, rax
    mov rbx, rax
    mov rsi, result_format
    mov rdx, float_start
    call sscanf
    pop rbp

    push rbp
    mov rbp, rsp
    mov rdi, qword [rel iters_num_entry]
    call gtk_entry_get_text
    mov rdi, rax
    mov rbx, rax
    mov rsi, iters_num_format
    mov rdx, int_iters_num
    call sscanf
    pop rbp
   
    mov rdi, qword [int_iters_num]
    movq xmm0, qword [float_start]
    movq xmm1, qword [float_end]

    call get_root
    
    push rbp
    mov rbp, rsp
    mov rdi, result_text_buffer
    mov rsi, result_format
    call sprintf
    pop rbp

    ; Creating and displaying a message window
    push rbp
    mov rbp, rsp

    ; Creating a new message window
    mov rdi, qword [rel window]
    mov rsi, 1                         ; GTK_DIALOG_MODAL
    mov rdx, 2                         ; Type of the message (GTK_MESSAGE_INFO)
    mov rcx, 1                         ; Buttons in the dialog box (GTK_BUTTONS_OK)
    mov r8, result_text_buffer         ; The text of the message
    call gtk_message_dialog_new
    
    mov qword [rel message_dialog], rax

    ; Displaying the message window
    mov rdi, qword [rel message_dialog]
    call gtk_dialog_run

    ; Destroying the message window after closing
    mov rdi, qword [rel message_dialog]
    call gtk_widget_destroy

    pop rbp
    
    ret
main:
    push rbp
    mov rbp, rsp
    xor rdi, rdi
    xor rsi, rsi
    call gtk_init
    ; сreating the window
    xor rdi, rdi
    call gtk_window_new
    mov qword [ rel window ], rax
    ; Setting the window title
    mov rdi, qword [ rel window ]
    mov rsi, title
    call gtk_window_set_title
    ; setting window sizes
    mov rdi, qword [ rel window ]
    mov rsi, GTK_WIN_WIDTH
    mov rdx, GTK_WIN_HEIGHT
    call gtk_window_set_default_size
    ; Setting the position of the window
    mov rdi, qword [ rel window ]
    mov rsi, GTK_WIN_POS_CENTER
    call gtk_window_set_position
    ; Binding the closing signal
    mov rdi, qword [ rel window ]
    mov rsi, signal.destroy
    mov rdx, _destroy_window    
    xor rcx, rcx
    xor r8d, r8d
    xor r9d, r9d
    call g_signal_connect_data

    mov rdi, GTK_ORIENTATION_HORIZONTAL
    mov rsi, LAYOUT_BOX_SPACING
    call gtk_box_new
    mov qword [rel layout_box], rax

    mov rdi, qword [rel window]
    mov rsi, qword [rel layout_box]
    call gtk_container_add

    ; Creating the start_x input field
    mov rdi, 0
    mov rsi, -1
    call gtk_entry_buffer_new
    mov qword [rel start_x_buffer], rax

    mov rdi, qword [rel start_x_buffer]
    call gtk_entry_new_with_buffer
    mov qword [rel start_x_entry], rax

    mov rdi, qword [rel start_x_entry]
    mov rsi, start_x_placeholder_text
    call gtk_entry_set_placeholder_text

    mov rdi, qword [rel layout_box]
    mov rsi, qword [rel start_x_entry]
    call gtk_container_add

    ; Creating the end_x  field
    mov rdi, 0
    mov rsi, -1
    call gtk_entry_buffer_new
    mov qword [rel end_x_buffer], rax

    mov rdi, qword [rel end_x_buffer]
    call gtk_entry_new_with_buffer
    mov qword [rel end_x_entry], rax
    
    mov rdi, qword [rel end_x_entry]
    mov rsi, end_x_placeholder_text
    call gtk_entry_set_placeholder_text

    mov rdi, qword [rel layout_box]
    mov rsi, qword [rel end_x_entry]
    call gtk_container_add

    ; The field for entering the number of iterations
    mov rdi, 0
    mov rsi, -1
    call gtk_entry_buffer_new
    mov qword [rel iters_num_buffer], rax

    mov rdi, qword [rel iters_num_buffer]
    call gtk_entry_new_with_buffer
    mov qword [rel iters_num_entry], rax
    
    mov rdi, qword [rel iters_num_entry]
    mov rsi, iters_num_placeholder_text
    call gtk_entry_set_placeholder_text

    mov rdi, qword [rel layout_box]
    mov rsi, qword [rel iters_num_entry]
    call gtk_container_add

    ; Creating a calculation button
    mov rdi, solve_button_title
    call gtk_button_new_with_label
    mov qword [rel solve_button], rax

    mov rdi, qword [rel layout_box]
    mov rsi, qword [rel solve_button]
    call gtk_container_add

    mov rdi, qword [ rel solve_button ]
    mov rsi, signal.clicked
    mov rdx, solve_command
    xor rcx, rcx
    xor r8d, r8d
    xor r9d, r9d
    call g_signal_connect_data


    ; Show the window
    mov rdi, qword [ rel window ]
    call gtk_widget_show_all
    call gtk_main
    ret
