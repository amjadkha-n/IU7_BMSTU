#include "../inc/my_snprintf.h"
/**
 * @brief The main function.
 * 
 * This function demonstrates the usage of the custom my_snprintf function by formatting a string
 * and printing the results using printf.
 *
 * @return Returns OK (0) to indicate successful execution.
 */
int main(void)
{
    char buffer_1[BUFFER_SIZE + 1];
    char buffer_2[BUFFER_SIZE + 1];

    char string[] = "checking";
    short int number = 12345;

    int n1 = my_snprintf(buffer_1, BUFFER_SIZE, "%c abc %hd %s", 'z', number, string);
    int n2 = snprintf(buffer_2, BUFFER_SIZE, "%c abc %hd %s", 'z', number, string);

    printf("%d, %s\n", n1, buffer_1);
    printf("%d, %s\n", n2, buffer_2);

    return OK;
}
