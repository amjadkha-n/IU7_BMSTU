#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>


void print_bin(uint32_t a)
{
    for (int i = 31; i >= 0; i--)
    {
        printf("%d", ((a >> i) & 1) ? 1 : 0); 
    }
} 

int main()
{
    uint32_t a;
    int n;
    if (scanf("%" SCNu32, &a) != 1)
    {
        printf("Error: Invalid input\n");
        return 1;
    }
    if (scanf("%d", &n) != 1 || n < 0)
    {
        printf("Error: Invalid input\n");
        return 1;
    }
    
    n %= 32; 

    a = (a << n) | (a >> (32 - n));

    printf("Result: ");
    print_bin(a);
    printf("\n");

    return 0;
}
