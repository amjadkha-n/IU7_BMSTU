/**
 * @file my_snprintf.h
 * @brief Header file for a custom snprintf implementation.
 */

#ifndef MY_SNPRINTF_H
#define MY_SNPRINTF_H

#include <stdarg.h>
#include <stdio.h>
#include <math.h>

/**
 * @brief Return code indicating success.
 *
 * This macro is used as a return code for functions to indicate success.
 */
#define OK 0

/**
 * @brief Size of the buffer used by my_snprintf.
 *
 * BUFFER_SIZE defines the size of the buffer used by the my_snprintf function for formatting strings.
 */
#define BUFFER_SIZE 100

/**
 * @brief Inserts a character into a buffer.
 *
 * This function is used to insert a character into the specified buffer at the current position
 * pointed to by buf_p. The buffer is considered to have a defined end at buf_end.
 *
 * @param buf_p A pointer to the current position in the buffer.
 * @param buf_end A pointer to the end of the buffer.
 * @param ch The character to insert into the buffer.
 */
void insert_char_into_buffer(char **buf_p, char *buf_end, char ch);

/**
 * @brief Inserts a string into a buffer.
 *
 * This function is used to insert a null-terminated string into the specified buffer at the current
 * position pointed to by buf_p. The buffer is considered to have a defined end at buf_end.
 *
 * @param argptr A va_list pointing to the variable arguments.
 * @param buf_p A pointer to the current position in the buffer.
 * @param buf_end A pointer to the end of the buffer.
 * @return Returns the number of characters inserted into the buffer.
 */
int insert_string_into_buffer(va_list argptr, char **buf_p, char *buf_end);

/**
 * @brief Formats a string and writes it to a buffer with a specified size.
 *
 * This function mimics the behavior of the standard snprintf function by formatting a string
 * according to a format specifier and writing the result to a buffer. It supports the format
 * specifiers '%c', '%hhd', and '%s'. The variable arguments are provided through a va_list.
 *
 * @param buffer A pointer to the buffer where the formatted string is written.
 * @param buf_size The size of the buffer.
 * @param format The format string containing format specifiers.
 * @param ... Additional arguments corresponding to the format specifiers.
 * @return Returns the number of characters (excluding the null terminator) that would be written
 * if the buffer were large enough. If an encoding error occurs, a negative value is returned.
 */
int my_snprintf(char *buffer, int buf_size, const char *format, ...);

#endif