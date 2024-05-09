#include "../inc/main.h"

/**
* @brief Main function for the program.
*
* This function is the entry point of the program. It reads input arguments, processes data, and performs sorting and filtering operations.
*
* @param argc The number of command-line arguments.
* @param argv An array of strings containing the command-line arguments.
* @return OK if the program executes successfully, or an error code on failure.
*/
int main(int argc, char **argv)
{
    int check = are_arguments_valid(argc, argv);
    
    if (check != OK)
        return check;

    int *arr = NULL, *end_arr = NULL;
    // Read and allocate memory for an array from a file
    check = read_array(argv[1], &arr, &end_arr);
    
    if (check != OK)
    {
        free_array(arr, end_arr);
        return check;
    }

    if (are_arguments_for_filter(argc, argv))
    {
        int *array_after_key = NULL, *end_array_after_key = NULL;

        void *hlib;
        fn_key_t key;

        hlib = dlopen("./key_lib/libkey.so", RTLD_NOW);
        if (!hlib)
        {
        
            fprintf(stderr, "Error: %s\n", dlerror());
            return CAN_NOT_OPEN_LIBRARY;
        }

        *(void **)(&key) = dlsym(hlib, "key");
        if (!key)
        {
            fprintf(stderr, "Error: %s\n", dlerror());
            dlclose(hlib);
            return CAN_NOT_LOAD_FUNCTION;
        }


        // Apply filter to the array
        check = key(arr, end_arr, &array_after_key, &end_array_after_key);
        dlclose(hlib);

        if (check != OK)
        {
            free_array(arr, end_arr);
            free_array(array_after_key, end_array_after_key);
            return check;
        }
        // Sort the filtered array
        mysort(array_after_key, end_array_after_key - array_after_key, sizeof(int), compare);
        // Print the sorted array to a file
        check = file_print_array(argv[2], array_after_key, end_array_after_key);
        free_array(array_after_key, end_array_after_key);
    }
    else
    {
        // Sort the original array
        mysort(arr, end_arr - arr, sizeof(int), compare);
        check = file_print_array(argv[2], arr, end_arr);
    }

    free_array(arr, end_arr);
    return check;
}

