#include "../inc/check_main.h"
/**
* @brief Check if command-line arguments are valid.
*
* This function checks if the number of command-line arguments is either 3 or 4 with a specific filter option.
*
* @param argc The number of command-line arguments.
* @param argv An array of strings containing the command-line arguments.
* @return OK if the arguments are valid, or ARG_ERROR if they are not.
*/
int are_arguments_valid(int argc, char **argv)
{
    int check = ARG_ERROR;

    // Check if the number of command-line arguments is either 3 or 4 with specific filter option
    if (argc == 3 || (argc == 4 && argv[3][0] == 'f' && argv[3][1] == 0))
    {
        check = OK;
    }
    // Return the result (OK or ARG_ERROR)
    return check;
}

/**
* @brief Check if command-line arguments indicate filtering.
*
* This function checks if the number of command-line arguments is 4 and if the filter option is specified.
*
* @param argc The number of command-line arguments.
* @param argv An array of strings containing the command-line arguments.
* @return 1 if filtering is indicated, 0 if not.
*/
int are_arguments_for_filter(int argc, char **argv)
{
    // Check if the number of command-line arguments is 4 and if the filter option is specified
    return (argc == 4 && argv[3][0] == 'f' && argv[3][1] == 0);  // Return true or false
}
