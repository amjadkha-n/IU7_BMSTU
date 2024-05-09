#include "associative_array.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

typedef struct element_t 
{
    char *key;
    int value;
} element_t;

struct assoc_array_type 
{
    element_t *elem;
    size_t size;
};

/**
 * @brief Duplicates a string.
 *
 * @param source The string to be duplicated.
 * @return A dynamically allocated copy of the input string.
 */
char *my_strdup(const char *source) 
{
    if (source == NULL)
    {
        return NULL;
    }

    size_t length = strlen(source) + 1;
    char *destination = (char *)malloc(length);

    if (destination != NULL)
    {
        strncpy(destination, source, length);
        destination[length - 1] = '\0';  // Ensure null-termination
    }

    return destination;
}

/**
 * @brief Creates an empty associative array.
 *
 * @return A pointer to the newly created associative array.
 */
assoc_array_t assoc_array_create(void) 
{
    assoc_array_t custom_array = (assoc_array_t)malloc(sizeof(struct assoc_array_type));

    if (custom_array != NULL) 
    {
        custom_array->elem = NULL;
        custom_array->size = 0;
    }

    return custom_array;
}
/**
 * @brief Destroys an associative array and frees associated memory.
 *
 * @param custom_arr A pointer to the associative array to be destroyed.
 */
void assoc_array_destroy(assoc_array_t *custom_arr) 
{
    if (custom_arr && *custom_arr) 
    {
        assoc_array_clear(*custom_arr);
        free((*custom_arr)->elem);
        free(*custom_arr);
        *custom_arr = NULL;
    }
}

/**
 * @brief Inserts a key-value pair into the associative array.
 *
 * @param custom_arr The associative array.
 * @param custom_key The key to insert.
 * @param custom_value The corresponding value.
 * @return An error code indicating the success or failure of the operation.
 */
assoc_array_error_t assoc_array_insert(assoc_array_t custom_arr, const char *custom_key, int custom_value) 
{
    // Check for invalid parameters
    if (!custom_arr || !custom_key || *custom_key == '\0')
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    // Check if the key already exists
    for (size_t i = 0; i < custom_arr->size; ++i)
    {
        if (strcmp(custom_arr->elem[i].key, custom_key) == 0)
        {
            return ASSOC_ARRAY_KEY_EXISTS;
        }
    }

    // Allocate memory for a new element
    element_t *new_elements = (element_t *)realloc(custom_arr->elem, (custom_arr->size + 1) * sizeof(element_t));
    if (!new_elements)
    {
        return ASSOC_ARRAY_MEM; // Memory allocation failed
    }

    // Update the array with the new element
    custom_arr->elem = new_elements;
    custom_arr->elem[custom_arr->size].key = my_strdup(custom_key);
    custom_arr->elem[custom_arr->size].value = custom_value;
    custom_arr->size++;

    return ASSOC_ARRAY_OK;
}
/**
 * @brief Finds the value associated with a given key in the associative array.
 *
 * @param arr The associative array.
 * @param key The key to search for.
 * @param num A pointer to an integer to store the found value.
 * @return An error code indicating the success or failure of the operation.
 */
assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    // Validate input parameters
    if (!arr || !key || !num || *key == '\0')
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    // Search for the key in the array
    for (size_t i = 0; i < arr->size; ++i)
    {
        if (strcmp(key, arr->elem[i].key) == 0)
        {
            // Return a pointer to the value associated with the key
            if (num)
            {
                *num = &(arr->elem[i].value);
            }
            return ASSOC_ARRAY_OK;
        }
    }

    // Key not found in the array
    return ASSOC_ARRAY_NOT_FOUND;
}

/**
 * @brief Removes a key-value pair from the associative array.
 *
 * @param arr The associative array.
 * @param key The key to remove.
 * @return An error code indicating the success or failure of the operation.
 */
assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key) 
{
    // Validate input parameters
    if (!arr || !key || *key == '\0')
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    // Search for the key in the array
    size_t found_index = SIZE_MAX;
    for (size_t i = 0; i < arr->size; ++i) 
    {
        if (strcmp(arr->elem[i].key, key) == 0) 
        {
            found_index = i;
            break;
        }
    }

    // Check if the key was found
    if (found_index != SIZE_MAX) 
    {
        free(arr->elem[found_index].key);

        // Shift elements to fill the gap
        for (size_t j = found_index; j < arr->size - 1; ++j) 
            arr->elem[j] = arr->elem[j + 1];

        // Resize the array
        element_t *new_elements = (element_t *)realloc(arr->elem, (arr->size - 1) * sizeof(element_t));
        if (!new_elements && arr->size > 1)
        {
            return ASSOC_ARRAY_MEM; // Memory allocation failed
        }

        arr->elem = new_elements;
        arr->size--;

        return ASSOC_ARRAY_OK;
    }

    // Key not found in the array
    return ASSOC_ARRAY_NOT_FOUND;
}

/**
 * @brief Clears all key-value pairs from the associative array.
 *
 * @param arr The associative array to be cleared.
 * @return An error code indicating the success or failure of the operation.
 */
assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    // Validate input parameter
    if (!arr)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    // Free individual keys
    for (size_t i = 0; i < arr->size; ++i)
    {
        free(arr->elem[i].key);
    }

    // Free the array of elements
    free(arr->elem);

    // Reset array size and element pointer
    arr->size = 0;
    arr->elem = NULL;

    return ASSOC_ARRAY_OK;
}

/**
 * @brief Performs a specified action for each element in the associative array.
 *
 * @param arr The associative array.
 * @param action The function pointer to the action to be performed.
 * @param param Additional parameter to be passed to the action function.
 * @return An error code indicating the success or failure of the operation.
 */
assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *value, void *param), void *param) 
{
    // Validate input parameters
    if (!arr || !action)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    // Perform the specified action for each element in the array
    for (size_t i = 0; i < arr->size; ++i)
    {
        action(arr->elem[i].key, &(arr->elem[i].value), param);
    }

    return ASSOC_ARRAY_OK;
}
/**
 * @brief Finds the minimum value in the associative array.
 *
 * @param arr The associative array.
 * @param num A pointer to an integer to store the minimum value.
 * @return An error code indicating the success or failure of the operation.
 */
assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    // Validate input parameters
    if (!arr || !num)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    // Check if the array is empty
    if (arr->size == 0)
    {
        return ASSOC_ARRAY_NOT_FOUND;
    }

    // Initialize min key and corresponding value
    const char *min_key = arr->elem[0].key;
    int *min_value = &(arr->elem[0].value);

    // Find the minimum key in the array
    for (size_t i = 1; i < arr->size; ++i)
    {
        if (strcmp(arr->elem[i].key, min_key) < 0)
        {
            min_key = arr->elem[i].key;
            min_value = &(arr->elem[i].value);
        }
    }

    *num = min_value;

    return ASSOC_ARRAY_OK;
}

/**
 * @brief Finds the maximum value in the associative array.
 *
 * @param arr The associative array.
 * @param num A pointer to an integer to store the maximum value.
 * @return An error code indicating the success or failure of the operation.
 */
assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    // Validate input parameters
    if (!arr || !num)
    {
        return ASSOC_ARRAY_INVALID_PARAM;
    }

    // Check if the array is empty
    if (arr->size == 0)
    {
        return ASSOC_ARRAY_NOT_FOUND;
    }

    // Initialize max key and corresponding value
    const char *max_key = arr->elem[0].key;
    int *max_value = &(arr->elem[0].value);

    // Find the maximum key in the array
    for (size_t i = 1; i < arr->size; ++i)
    {
        if (strcmp(arr->elem[i].key, max_key) > 0)
        {
            max_key = arr->elem[i].key;
            max_value = &(arr->elem[i].value);
        }
    }

    *num = max_value;

    return ASSOC_ARRAY_OK;
}

