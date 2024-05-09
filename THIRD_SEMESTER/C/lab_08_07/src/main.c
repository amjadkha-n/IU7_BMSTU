#include <stdio.h>
#include "../inc/constants.h"
#include "../inc/matrix.h"
#include "../inc/matrix_in_out.h"
#include "../inc/operations.h"
/**
 * @brief Main function for performing matrix operations.
 * 
 * This function reads and loads matrices, trims them, makes them even, multiplies
 * them, and displays the result. If any of these operations fail, it returns an error code.
 * 
 * @return An error code indicating the success or failure of the program.
 */
int main(void)
{
    matrix_t a = { NULL, 0, 0 }, b = { NULL, 0, 0 }, c = { NULL, 0, 0 };
    int check = OK;

    check = read_and_load_matrices(&a, &b);

    if (check == OK)
    {
        check = trim_matrices(&a, &b);

        if (check == OK)
        {
            check = make_matrices_even(&a, &b);

            if (check == OK)
            {
                check = multiply_and_store_matrices(a, b, &c);

                if (check == OK)
                {
                    display_result(c);
                }
            }
        }
    }

    free_all_matrixes(&a, &b, &c);
    return check;
}
