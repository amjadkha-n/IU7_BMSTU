#include "../inc/main.h"

node_t *sort(node_t *head, int (*comparator)(const void*, const void*)) 
{
    node_t *sorted_head = NULL;
    node_t *current = head;

    while (current) 
    {
        node_t *next = current->next;
        sorted_insert(&sorted_head, current, comparator);
        current = next;
    }

    return sorted_head;
}


void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void*, const void*)) 
{
    node_t **current_node = head;

    while (*current_node != NULL && comparator(element->data, (*current_node)->data) >= 0) 
    {
        current_node = &(*current_node)->next;
    }

    element->next = *current_node;
    *current_node = element;
}

void add_new_elem(node_t *prev_elem, node_t *next_elem, node_t *element, node_t **head) 
{
    if (!prev_elem) 
    {
        element->next = next_elem;
        *head = element;
    } 
    else 
    {
        prev_elem->next = element;
        element->next = next_elem;
    }

    fprintf(stderr, "%d\n", *(int*)element->data);
}

