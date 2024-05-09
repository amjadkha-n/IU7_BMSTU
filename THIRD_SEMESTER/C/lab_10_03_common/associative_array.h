#ifndef ASSOC_ARR_H__
#define ASSOC_ARR_H__

/**
 * @file assoc_arr.h
 * @brief Header file for defining an associative array data structure and its related operations.
 */

/**
 * @brief Opaque structure representing an associative array.
 */
typedef struct assoc_array_type *assoc_array_t;

/**
 * @brief Enumeration defining error codes for associative array operations.
 */
typedef enum error_t
{
    ASSOC_ARRAY_OK = 0,             /**< Operation completed successfully. */
    ASSOC_ARRAY_INVALID_PARAM,      /**< Invalid parameter passed to the function. */
    ASSOC_ARRAY_MEM,                /**< Memory allocation failure. */
    ASSOC_ARRAY_NOT_FOUND,          /**< Element not found in the associative array. */
    ASSOC_ARRAY_KEY_EXISTS,         /**< Attempted to insert an element with an existing key. */
} assoc_array_error_t;

/**
 * @brief Creates a new associative array.
 * @return A pointer to the newly created associative array.
 */
assoc_array_t assoc_array_create(void);

/**
 * @brief Destroys the given associative array, freeing allocated memory.
 * @param arr A pointer to the associative array to be destroyed. The pointer will be set to NULL after destruction.
 */
void assoc_array_destroy(assoc_array_t *arr);

/**
 * @brief Inserts an element into the associative array with the given key and value.
 * @param arr The associative array.
 * @param key The key for the element.
 * @param num The value to be associated with the key.
 * @return An error code indicating the result of the operation.
 */
assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num);

/**
 * @brief Finds the element with the given key in the associative array.
 * @param arr The associative array.
 * @param key The key to search for.
 * @param num A pointer to store the found value.
 * @return An error code indicating the result of the operation.
 */
assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num);

/**
 * @brief Removes the element with the given key from the associative array.
 * @param arr The associative array.
 * @param key The key of the element to be removed.
 * @return An error code indicating the result of the operation.
 */
assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key);

/**
 * @brief Clears all elements from the associative array, freeing associated memory.
 * @param arr The associative array to be cleared.
 * @return An error code indicating the result of the operation.
 */
assoc_array_error_t assoc_array_clear(assoc_array_t arr);

/**
 * @brief Applies a custom action to each element in the associative array.
 * @param arr The associative array.
 * @param action A function pointer representing the action to be performed on each element.
 * @param param An additional parameter to be passed to the action function.
 * @return An error code indicating the result of the operation.
 */
assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param);

/**
 * @brief Finds the minimum value in the associative array.
 * @param arr The associative array.
 * @param num A pointer to store the minimum value.
 * @return An error code indicating the result of the operation.
 */
assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num);

/**
 * @brief Finds the maximum value in the associative array.
 * @param arr The associative array.
 * @param num A pointer to store the maximum value.
 * @return An error code indicating the result of the operation.
 */
assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num);

#endif
