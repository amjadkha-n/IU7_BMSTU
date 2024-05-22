global get_root

%define x_start xmm0
%define x_end xmm1
%define iters_num rdi
section .data 
    epsilon dq 0.000001
    fmt_double db "%lf", 10, 0
    x dq 0
    answer dq 0
    adder dq 7
    tmp_a dq 0
    tmp_b dq 0

    tmp_x_start dq 0
    tmp_x_end dq 0
section .text

    extern printf 

delta_func:
    ; a
    fld qword [tmp_a]
    ; b -a
    fld qword [tmp_b]
    fld qword [tmp_a]
    fsubp
    

    ; (b - a) * f(a)
    fld qword [tmp_a]
    fstp qword [x]
    call func
    fmulp

    ; f(b) - f(a)
    fld qword [tmp_b]
    fstp qword [x]
    call func

    fld qword [tmp_a]
    fstp qword [x]
    call func

    fsubp

    ; (b - a) * f(x) / (f(b) - f(a))
    fdivp
    ;a - (b - a) * f(a) / (f(b) - f(a))
    fsubp
    ret
func:
    ;x * x
    fld qword [x] 
    fld qword [x] 
    fmulp
    ; x * x * x
    fld qword [x]
    fmulp
    ; x ^ 3 + 7
    fild qword [adder]
    faddp
    ; cos(x^3 + 7)
    fcos
    ret
get_root:

    movsd [tmp_x_start], x_start
    movsd [tmp_x_end], x_end

    get_root_loop:

    ; while (fabs(b - a) > eps)
    fld qword [tmp_x_end]
    fld qword [tmp_x_start]
    fsubp
    fabs
    fld qword [epsilon]
    fcompp
    fstsw ax 
    fwait    
    sahf     
    jnb exit

    cmp rdi, 0
    jle exit

    mov rax, qword [tmp_x_start]
    mov [tmp_a], rax
    mov rax, qword [tmp_x_end]
    mov [tmp_b],  rax
    call delta_func
    fstp qword [tmp_x_start]

    mov rax, qword [tmp_x_end]
    mov [tmp_a], rax
    mov  rax ,  qword [tmp_x_start]
    mov [tmp_b], rax
    call delta_func
    fstp qword [tmp_x_end]

    dec rdi
    jmp get_root_loop

    exit:

    movsd xmm0, qword [tmp_x_end]
    ret
