# include "stddef.h"
# include <iostream>

#define OK 0
size_t string_len(const char *str)
{
    size_t len = 0;
    
    asm volatile
    (
        "mov x0, %1\n"
        "mov x1, #0\n"
        "1:\n"
        "ldrb w2, [x0], #1\n"
        "cbz w2, 2f\n"
        "add x1, x1, #1\n"
        "b 1b\n"
        "2:\n"
        "mov %0, x1\n"
        : "=r" (len)
        : "r" (str)
        : "x0", "x1", "w2"
    );
    return len;
}

int main(int argc, char *argv[])
{
    char string[] = "Hello world!";

    std::cout << "String: " << string << "\n";
    std::cout << "Length: " << string_len(string) << "\n";

    return OK;   
}