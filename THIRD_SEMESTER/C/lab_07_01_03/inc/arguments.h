#ifndef _ARGUMENTS_H_

#define _ARGUMENTS_H_
/**
* @brief Check if command-line arguments are valid.
*
* This function checks if the number of command-line arguments is either 3 or 4 with a specific filter option.
*
* @param argc The number of command-line arguments.
* @param argv An array of strings containing the command-line arguments.
* @return OK if the arguments are valid, or ARG_ERROR if they are not.
*/	
int are_arguments_valid(int argc, char **argv);
/**
* @brief Check if command-line arguments indicate filtering.
*
* This function checks if the number of command-line arguments is 4 and if the filter option is specified.
*
* @param argc The number of command-line arguments.
* @param argv An array of strings containing the command-line arguments.
* @return 1 if filtering is indicated, 0 if not.
*/
int are_arguments_for_filter(int argc, char **argv);

#endif
