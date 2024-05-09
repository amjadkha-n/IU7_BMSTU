#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "my_string_len.h"

size_t my_asm_len(const char *const string)
{
    size_t len = 0;

    __asm__
    (
        ".intel_syntax noprefix\n"
        "mov rcx, -1\n"
        "mov rdi, %1\n"
        "mov al, 0\n"

        "repne scasb\n"

        "neg rcx\n"

        "sub rcx, 2\n"

        "mov %0, rcx\n"

        : "=r" (len)
        : "r" (string)

        : "rcx", "al", "rdi"
    );
    return len;
}