#include "../inc/main.h"

int comparator(const void *element_1, const void *element_2) 
{
    int value1 = *((int*) element_1);
    int value2 = *((int*) element_2);

    if (value1 < value2) 
    {
        return -1;
    } 
    else if (value1 > value2) 
    {
        return 1;
    } 
    else 
    {
        return 0;
    }
}


node_t *search_list(node_t *head, const void *data, int (*comparator)(const void*, const void*)) 
{
    node_t *current_node = head;

    while (current_node != NULL) 
    {
        if (comparator(data, current_node->data) == 0) 
        {
            return current_node;
        }

        current_node = current_node->next;
    }

    return NULL;
}

void *remove_first_node(node_t **head) 
{
    if (head == NULL || *head == NULL) 
        return NULL;

    void *removed_data = (*head)->data;

    node_t *temp = *head;
    *head = (*head)->next;

    free(temp);

    return removed_data;
}

node_t *reverse_list(node_t *head) 
{
    node_t *reversed_head = NULL;

    while (head != NULL) 
    {
        node_t *current_node = head;
        head = head->next;

        current_node->next = reversed_head;
        reversed_head = current_node;
    }

    return reversed_head;
}

void free_list(node_t *head) 
{
    while (head != NULL) 
    {
        node_t *current_node = head;
        head = head->next;

        free(current_node);
    }
}

int custom_list_operation(node_t **head, salary_t *array) 
{
    if (*head == NULL) 
        return EMPTY_LIST;

    *head = sort(*head, comparator);

    node_t *target_node = search_list(*head, array->array, comparator);

    if (target_node != *head) 
    {
        remove_first_node(head);
    } 
    else 
    {
        *head = reverse_list(*head);

        if (*head == NULL) 
            return MEMORY_ALLOCATION_FAILURE;

        target_node = search_list(*head, array->array, comparator);

        if (target_node != *head) 
        {
            remove_first_node(head);
        }
    }

    return OK;
}

