#include "../inc/main.h"

/**
* @brief Compare two integers.
*
* This function compares two integers and returns 1 if the first is greater, -1 if the second is greater, or 0 if they are equal.
*
* @param p_1 Pointer to the first integer.
* @param p_2 Pointer to the second integer.
* @return 1 if the first integer is greater, -1 if the second is greater, or 0 if they are equal.
*/
int compare(const void *p_1, const void *p_2)
{
    int check;
    const int *p_int_1 = p_1;
    const int *p_int_2 = p_2;
    if (*p_int_1 > *p_int_2)
    {
        check = 1;
    }
    else if (*p_int_1 < *p_int_2)
    {
        check = -1;
    }
    else
    {
        check = 0;
    }
    return check;
}
/**
* @brief Swap two memory regions.
*
* This function swaps the contents of two memory regions of the specified size.
*
* @param a Pointer to the first memory region.
* @param b Pointer to the second memory region.
* @param size Size of each element in the memory regions.
*/
void swap(void *a, void *b, size_t size)
{
    char *a_ptr = a;
    char *b_ptr = b;
    char t;
    // Initialize a counter for bytes swapped
    size_t i = 0;

    while (i < size)
    {
        t = *a_ptr;
        // Swap the bytes at a and b
        *a_ptr = *b_ptr;
        *b_ptr = t;
        // Move to the next byte in a
        a_ptr++;
        // Move to the next byte in b
        b_ptr++;
        // Increment the byte counter
        i++;
    }
}

/**
* @brief Sort an array using the bubble sort algorithm.
*
* This function sorts an array using the bubble sort algorithm with the provided comparison function.
*
* @param base Pointer to the start of the array.
* @param nmemb Number of elements in the array.
* @param size Size of each element in the array.
* @param compar Comparison function for elements.
*/
void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void*, const void*))
{
    // Create a pointer to the beginning of the array
    char *base_beg = base;
    // Create a pointer to the end of the array
    char *base_end = base_beg + nmemb * size;
    
    for (char *ptr_i = base_beg; ptr_i < base_end - size; ptr_i += size)
    {
        for (char *ptr_j = base_beg; ptr_j < base_end - size; ptr_j += size)
        {
            // Compare adjacent elements using compar function
            if (compar(ptr_j, ptr_j + size) > 0)
            {
                // Swap elements if out of order
                swap(ptr_j, ptr_j + size, size); 
            }
        }
    }
}