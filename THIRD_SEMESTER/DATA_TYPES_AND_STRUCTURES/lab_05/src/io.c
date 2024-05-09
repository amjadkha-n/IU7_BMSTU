#include <stdio.h>
#include <stdlib.h>
#include "../inc/io.h"
/**
 * @brief Prints the main menu for queue handling.
 */
void print_hello()
{
    printf("%s%s",
           "\n\nQUEUE HANDLING:\n\n",
           "1 - Modeling and characterization for an array queue.\n"
           "2 - Modeling and characterization for a queue in the form of a list.\n"
           "3 - Change the application processing time.\n"
           "4 - Output of time comparison when performing operations.\n"
           "0 - Exiting the program.\n\n"
           );
}
/**
 * @brief Clears the input buffer.
 */
void clean_my()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}
/**
 * @brief Checks and retrieves a floating-point number from the user.
 *
 * @param number Pointer to the variable where the number will be stored.
 * @return int Status code: OK if successful, DONT_INT_NUM_CHOICE if input is not a valid number.
 */
int check_float(double *const number)
{
    char num[3];
    char *n;
    fflush(stdin);
    n = fgets(num, 4, stdin);
    if (n == NULL || num[0] == '\n')
        return DONT_INT_NUM_CHOICE;
    num[strlen(num) - 1] = '\0';
    *number = (double)atof(num);

    return OK;
}
/**
 * @brief Checks and retrieves an integer number within a specified range from the user.
 *
 * @param number Pointer to the variable where the number will be stored.
 * @param l Lower bound of the valid range.
 * @param r Upper bound of the valid range.
 * @return int Status code: OK if successful, INV_NUM_CHOICE if input is not a valid number within the range.
 */
int check_number(int *number, const int l, const int r)
{
    printf("Entering a menu item: ");
    char num[1];
    scanf("%s", num);

    *number = num[0] - '0';

    if (*number < l || *number > r)
        return INV_NUM_CHOICE;

    return OK;
}
/**
 * @brief Prints the current and average length of a queue.
 *
 * @param queue Pointer to the queue structure.
 */
void len_swow(queue_r *queue)
{
    printf("Current queue length %s: \t %d\n", queue->name, queue->tmp_len);
    if (queue->count_req > 0)
    {
        printf("Average queue length %s: \t %lf\n", queue->name,
                (double)queue->sum_len / (double)queue->count_req);
    }
}
