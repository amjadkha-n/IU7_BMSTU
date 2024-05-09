#include "operations.h"

// Define error codes for the program.
#define INT_OVERFLOW_ERROR 1
#define INT_INPUT_ERROR 2
#define FLOAT_OVERFLOW_ERROR 3
#define FLOAT_INPUT_ERROR 4
#define EMPTY_MANTISSE_ERROR 5
#define FLOAT_ORDER_OVERFLOW_ERROR 6

int main() {
    char int_str[STR_LEN]; // Declare a character array for storing an integer string.
    char float_str[STR_LEN]; // Declare a character array for storing a floating-point string.
    bigint_t int_num = {.data = {0}, .data_len = 0}; // Declare and initialize a bigint_t variable for integers.
    bigfloat_t float_num = {.mantisse = {0}, .mantisse_len = 0}; // Declare and initialize a bigfloat_t variable for floats.
    bigfloat_t res = {.mantisse = {0}, .mantisse_len = 0}; // Declare and initialize a bigfloat_t variable for the result.
    int rc = 0; // Declare an integer variable for error codes and return values.

    printf("Enter an integer:\n");
    printf("+---------1---------2---------3\n");
    read_str(int_str, STR_LEN); // Read a string from the user and store it in int_str.

    rc = str_to_bigint(&int_num, int_str); // Convert the integer string to a bigint.

    if (rc == 1)
    {
        printf("Integer overflow\n");
        return INT_OVERFLOW_ERROR;
    } 
    else if (rc == 2)
    {
        printf("Error when entering an integer\n");
        return INT_INPUT_ERROR;
    }

    printf("Enter a real number:\n");
    printf("+---------1---------2---------3---------4\n");
    read_str(float_str, STR_LEN); // Read a string from the user and store it in float_str.

    rc = str_to_bigfloat(&float_num, float_str); // Convert the floating-point string to a bigfloat.

    if (rc == 1)
    {
        printf("Error when entering a real number\n");
        return FLOAT_INPUT_ERROR;
    }
    else if (rc == 2)
    {
        printf("Overflow of a real number\n");
        return FLOAT_OVERFLOW_ERROR;
    }
    else if (rc == 3)
    {
        printf("The mantissa is missing\n");
        return EMPTY_MANTISSE_ERROR;
    }
    else if (rc == 4)
    { 
        printf("Overflow of the order of a real number\n");
        return FLOAT_ORDER_OVERFLOW_ERROR;
    }

    rc = bigint_to_bigfloat_multiplication(&res, &int_num, &float_num); // Multiply the integer and float.

    if (rc == 1)
    {
        printf("Overflow of the order of a real number\n");
        return FLOAT_ORDER_OVERFLOW_ERROR;
    }

    print_bigint(&int_num); // Print the integer.
    printf(" * ");
    print_bigfloat(&float_num);
    printf(" = ");
    print_bigfloat(&res);
    printf("\n");

    return EXIT_SUCCESS;
}
