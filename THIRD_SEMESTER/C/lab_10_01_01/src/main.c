#include "../inc/main.h"

int main(int argc, const char *argv[])
{
    int rc;

    if (argc != 3)
    {
        return ARGUMENT_ERROR;
    }

    FILE *input_file, *output_file;
    
    input_file = fopen(argv[1], "r");
    
    if (!input_file)
    {
        return MISSING_FILE;
    }

    salary_t data_array;

    rc = read_salary_array(&data_array, input_file);

    if (rc)
    {
        return rc;
    }

    if (fclose(input_file))
    {
        return FILE_CLOSE_ERROR;
    }

    node_t *list_head = NULL;

    rc = fill_linked_list(&list_head, &data_array);

    if (rc)
    {
        return rc;
    }

    rc = custom_list_operation(&list_head, &data_array);

    if (rc)
    {
        return rc;
    }

    output_file = fopen(argv[2], "w");
    
    if (!output_file)
    {
        return MISSING_FILE;
    }

    print_linked_list(list_head, output_file);

    if (fclose(output_file))
    {
        return FILE_CLOSE_ERROR;
    }

    if (list_head != NULL)
    {
        free_list(list_head);
    }

    if (data_array.array != NULL)
    {
        free(data_array.array);
    }

    return OK;
}
