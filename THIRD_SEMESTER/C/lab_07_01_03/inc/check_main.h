#include <string.h>
#include <stdlib.h>
#include <stdint.h>
/**
 * @file
 * @brief This header file defines constants and error codes for dynamic array operations.
 */

#ifndef _DYNAMIC_ARRAY_H_
#define _DYNAMIC_ARRAY_H_

/**
 * @def OK
 * @brief The operation was successful.
 */
#define OK 0

/**
 * @def ARG_ERROR
 * @brief An error occurred due to invalid function arguments.
 */
#define ARG_ERROR -1

/**
 * @def INPUT_FILE_ERROR
 * @brief An error occurred while opening or accessing an input file.
 */
#define INPUT_FILE_ERROR -2

/**
 * @def READ_ERROR
 * @brief An error occurred while reading data.
 */
#define READ_ERROR -3

/**
 * @def MEMORY_ERROR
 * @brief An error occurred due to memory allocation failure.
 */
#define MEMORY_ERROR -4

/**
 * @def KEY_ERROR
 * @brief An error occurred during a key operation.
 */
#define KEY_ERROR -5

/**
 * @def OUTPUT_FILE_ERROR
 * @brief An error occurred while opening or accessing an output file.
 */
#define OUTPUT_FILE_ERROR -6

#endif
