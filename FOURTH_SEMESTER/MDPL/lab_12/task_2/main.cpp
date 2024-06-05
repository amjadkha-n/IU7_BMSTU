# include <iostream>
# include <stddef.h>

# define OK 0

void neon_addition(const int *a, const int *b, int *c, int n)
{
    int i = 0;
    for (i = 0; i < (n / 4) * 4; i += 4)
    {
        asm volatile
        (
            "ld1 {v0.4s}, [%[a]]\n"
            "ld1 {v1.4s}, [%[b]]\n"

            "add v2.4s, v0.4s, v1.4s\n"

            "st1 {v2.4s}, [%[c]]\n"
            // :
            :
            : [a]"r" (&a[i]), [b] "r" (&b[i]), [c] "r" (&c[i])
            : "v0", "v1", "v2"
        ); 
    }
    for (; i < n; i++)
    {
        asm volatile
        (
            "ldr w0, [%[a]]\n"
            "ldr w1, [%[b]]\n"

            "add w2, w0, w1\n"

            "str w2, [%[c]]\n"

            :
            : [a]"r" (&a[i]), [b]"r"(&b[i]), [c]"r" (&c[i])
            : "w0", "w2", "w1"
        );
    }
}

int main(int argc, char *argv[])
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int b[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int c[9];
    int n = sizeof(c) / sizeof(int);

    neon_addition(a, b, c, n);
    std::cout << "Neon Addition: " << "\n";
    for (int i = 0; i < n; i++)
    {
        std::cout << c[i] << " ";
    }
    std::cout << "\n";

    return OK;
}
