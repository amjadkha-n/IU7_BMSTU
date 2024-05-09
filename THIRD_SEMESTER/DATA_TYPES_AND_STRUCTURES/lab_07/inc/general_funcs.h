#ifndef __GENERAL_FUNCS_H__
#define __GENERAL_FUNCS_H__
/**
 * @brief Flushes the input buffer.
 * 
 * This function reads characters from the standard input buffer until a newline character is encountered,
 * effectively flushing the input buffer.
 */
void input_flush(void);
/**
 * @brief Prints the menu for the program.
 * 
 * This function prints a menu with various options for working with trees of words, hash tables, and time experiments.
 */
void print_menu(void);

#endif // __GENERAL_FUNCS_H__