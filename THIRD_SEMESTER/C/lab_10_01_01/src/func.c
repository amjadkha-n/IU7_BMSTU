#include "../inc/main.h"

void print_linked_list(node_t *head, FILE *f) 
{
    node_t *current_node = head;

    while (current_node != NULL) 
    {
        int *data_ptr = (int *)current_node->data;
        fprintf(f, "%d\n", *data_ptr);
        current_node = current_node->next;
    }
}


int read_salary_array(salary_t *array, FILE *f) 
{
    array->array = NULL;
    array->size = 0;

    int initial_capacity = 5;
    int *buffer = malloc(initial_capacity * sizeof(int));

    if (!buffer) 
        return MEMORY_ALLOCATION_FAILURE;

    int value;
    
    while (fscanf(f, "%d", &value) == 1) 
    {
        if (array->size >= initial_capacity) 
        {
            int new_capacity = initial_capacity * 2;
            int *new_buffer = realloc(buffer, new_capacity * sizeof(int));

            if (!new_buffer) 
            {
                free(buffer);
                return MEMORY_ALLOCATION_FAILURE;
            }

            buffer = new_buffer;
            initial_capacity = new_capacity;
        }

        buffer[array->size++] = value;
    }

    array->array = buffer;
    return OK;
}

int fill_linked_list(node_t **head, salary_t *array) 
{
    node_t *tail = NULL;

    for (int i = 0; i < array->size; i++) 
    {
        node_t *new_node = malloc(sizeof(node_t));

        if (!new_node) 
            return MEMORY_ALLOCATION_FAILURE;

        new_node->data = &(array->array[i]);
        new_node->next = NULL;

        if (*head == NULL) 
        {
            *head = new_node;
            tail = new_node;
        } 
        else 
        {
            tail->next = new_node;
            tail = new_node;
        }
    }

    return OK;
}

