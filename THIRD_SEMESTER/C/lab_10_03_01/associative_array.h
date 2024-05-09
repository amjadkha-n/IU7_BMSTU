#ifndef ASSOC_ARR_H__
#define ASSOC_ARR_H__

/**
 * @file assoc_arr.h
 * @brief Header file for the associative array implementation.
 */

/**
 * @brief Type definition for the associative array structure.
 */
typedef struct assoc_array_type *assoc_array_t;

/**
 * @brief Enumeration defining error codes for associative array operations.
 */
typedef enum error_t
{
    ASSOC_ARRAY_OK,
    ASSOC_ARRAY_INVALID_PARAM,
    ASSOC_ARRAY_MEM,
    ASSOC_ARRAY_NOT_FOUND,
    ASSOC_ARRAY_KEY_EXISTS
} assoc_array_error_t;

/**
 * @brief Creates an empty associative array.
 *
 * @return A pointer to the newly created associative array.
 */
assoc_array_t assoc_array_create(void);

/**
 * @brief Destroys an associative array and frees associated memory.
 *
 * @param arr A pointer to the associative array to be destroyed.
 */
void assoc_array_destroy(assoc_array_t *arr);

/**
 * @brief Inserts a key-value pair into the associative array.
 *
 * @param arr The associative array.
 * @param key The key to insert.
 * @param num The corresponding value.
 * @return An error code indicating the success or failure of the operation.
 */
assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num);

/**
 * @brief Finds the value associated with a given key in the associative array.
 *
 * @param arr The associative array.
 * @param key The key to search for.
 * @param num A pointer to an integer to store the found value.
 * @return An error code indicating the success or failure of the operation.
 */
assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num);

/**
 * @brief Removes a key-value pair from the associative array.
 *
 * @param arr The associative array.
 * @param key The key to remove.
 * @return An error code indicating the success or failure of the operation.
 */
assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key);

/**
 * @brief Clears all key-value pairs from the associative array.
 *
 * @param arr The associative array to be cleared.
 * @return An error code indicating the success or failure of the operation.
 */
assoc_array_error_t assoc_array_clear(assoc_array_t arr);

/**
 * @brief Performs a specified action for each element in the associative array.
 *
 * @param arr The associative array.
 * @param action The function pointer to the action to be performed.
 * @param param Additional parameter to be passed to the action function.
 * @return An error code indicating the success or failure of the operation.
 */
assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param);

/**
 * @brief Finds the minimum value in the associative array.
 *
 * @param arr The associative array.
 * @param num A pointer to an integer to store the minimum value.
 * @return An error code indicating the success or failure of the operation.
 */
assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num);

/**
 * @brief Finds the maximum value in the associative array.
 *
 * @param arr The associative array.
 * @param num A pointer to an integer to store the maximum value.
 * @return An error code indicating the success or failure of the operation.
 */
assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num);

#endif // ASSOC_ARR_H__
