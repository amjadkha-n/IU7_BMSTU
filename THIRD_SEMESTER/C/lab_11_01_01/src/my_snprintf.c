#include <stdbool.h>
#include "../inc/my_snprintf.h"

/**
 * @brief Inserts a character into a buffer.
 *
 * This function inserts a character into the specified buffer at the current position pointed to by
 * buf_p. The buffer is considered to have a defined end at buf_end. If there is space in the buffer,
 * the character is inserted, and the buffer position is incremented.
 *
 * @param buf_p A pointer to the current position in the buffer.
 * @param buf_end A pointer to the end of the buffer.
 * @param ch The character to insert into the buffer.
 */
void insert_char_into_buffer(char **buf_p, char *buf_end, char ch)
{
    if (*buf_p < buf_end)
    {
        **buf_p = ch;
        (*buf_p)++;
    }
}

/**
 * @brief Inserts an integer into a buffer.
 *
 * This function formats an integer and inserts its characters into the specified buffer at the
 * current position pointed to by buf_p. The buffer is considered to have a defined end at buf_end.
 * The function also accounts for the sign of the integer and increments the buffer position accordingly.
 *
 * @param argptr A va_list pointing to the variable arguments.
 * @param buf_p A pointer to the current position in the buffer.
 * @param buf_end A pointer to the end of the buffer.
 * @return Returns the number of characters inserted into the buffer.
 */
int insert_number_into_buffer(va_list argptr, char **buf_p, char *buf_end)
{
    int char_in_buf = 0;
    char ch;

    int number = va_arg(argptr, int);

    if (number < 0)
    {
        insert_char_into_buffer(buf_p, buf_end, '-');
        char_in_buf++;

        number = -number;
    }

    int divisor = 1;
    while (divisor <= number / 10)
    {
        divisor *= 10;
    }

    while (divisor > 0)
    {
        ch = '0' + number / divisor;
        insert_char_into_buffer(buf_p, buf_end, ch);
        char_in_buf++;

        number %= divisor;
        divisor /= 10;
    }

    return char_in_buf;
}

/**
 * @brief Inserts a string into a buffer.
 *
 * This function inserts a null-terminated string into the specified buffer at the current position
 * pointed to by buf_p. The buffer is considered to have a defined end at buf_end. The function
 * increments the buffer position for each character in the string.
 *
 * @param argptr A va_list pointing to the variable arguments.
 * @param buf_p A pointer to the current position in the buffer.
 * @param buf_end A pointer to the end of the buffer.
 * @return Returns the number of characters inserted into the buffer.
 */
int insert_string_into_buffer(va_list argptr, char **buf_p, char *buf_end)
{
    int char_in_buf = 0;

    char *str = va_arg(argptr, char*);

    while (*str != '\0')
    {
        insert_char_into_buffer(buf_p, buf_end, *str++);
        char_in_buf++;
    }

    return char_in_buf;
}

/**
 * @brief Formats a string and writes it to a buffer with a specified size.
 *
 * This function mimics the behavior of the standard snprintf function by formatting a string
 * according to a format specifier and writing the result to a buffer. It supports the format
 * specifiers '%c', '%hhd', and '%s'. The variable arguments are provided through a va_list.
 *
 * @param buf_p A pointer to the buffer where the formatted string is written.
 * @param buf_size The size of the buffer.
 * @param format The format string containing format specifiers.
 * @param ... Additional arguments corresponding to the format specifiers.
 * @return Returns the number of characters (excluding the null terminator) that would be written
 * if the buffer were large enough. If an encoding error occurs, a negative value is returned.
 */
int my_snprintf(char *buf_p, int buf_size, const char *format, ...)
{
    va_list argptr;
    va_start(argptr, format);

    char *buf_end = buf_p + buf_size;
    int char_in_buf = 0;

    while (*format != '\0')
    {
        char ch;
        if (*format == '%')
        {
            format++;
            
            switch (*format)
            {
                case 'c':
                    ch = va_arg(argptr, int);
                    insert_char_into_buffer(&buf_p, buf_end, ch);
                    char_in_buf++;
                    break;
                case 'h':
                    if (*(format + 1) == 'd')
                    {
                        char_in_buf += insert_number_into_buffer(argptr, &buf_p, buf_end);
                        format++;
                    }
                    break;
                case 's':
                    char_in_buf += insert_string_into_buffer(argptr, &buf_p, buf_end);
                    break;
                default:
                    insert_char_into_buffer(&buf_p, buf_end, *format);
                    char_in_buf++;
                    break;
            }
        }
        else
        {
            insert_char_into_buffer(&buf_p, buf_end, *format);
            char_in_buf++;
        }

        format++;
    }

    if (buf_p < buf_end)
    {
        *buf_p = '\0';
    }
    else if (buf_size > 0)
    {
        *(--buf_p) = '\0';
    }

    va_end(argptr);
    return char_in_buf;
}
