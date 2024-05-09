section .text

global my_asm_copy

my_asm_copy:
    
    mov rbx, rdi
    mov rcx, rdx

    cmp rdi, rsi

    jbe copy 

    mov rax, rdi
    sub rax, rsi
    cmp rax, rcx
    
    ja copy

    add rdi, rcx
    add rsi, rcx

    dec rdi
    dec rsi

    std

copy:
    rep movsb

    cld

    mov byte [rbx + rdx], 0

quit:
    ret

