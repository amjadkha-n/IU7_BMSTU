#include "../inc/main.h"

int display_number_as_list(void)
{
    int number, rc;
    
    if ((rc = read_number(&number)) != OK)
        return rc;

    node_t *head = NULL;

    if ((rc = fill_the_list(&head, number)) != OK)
    {
        free_linked_list(head);
        return rc;
    }

    print_linked_list(head);
    free_linked_list(head);

    return OK;
}

int multiplication_of_two_numbers(void)
{
    int first_numb, rc;

    if ((rc = read_number(&first_numb)) != OK)
        return rc;

    node_t *first_head = NULL;

    if ((rc = fill_the_list(&first_head, first_numb)) != OK)
    {
        free_linked_list(first_head);
        return rc;
    }

    int second_numb;

    if ((rc = read_number(&second_numb)) != OK)
    {
        free_linked_list(first_head);
        return rc;
    }

    node_t *second_head = NULL;

    if ((rc = fill_the_list(&second_head, second_numb)) != OK)
    {
        free_linked_list(first_head);
        free_linked_list(second_head);
        return rc;
    }

    node_t *res_head = multiply_numbers(first_head, second_head);

    print_linked_list(res_head);

    free_linked_list(first_head);
    free_linked_list(second_head);

    return OK;
}

int squaring_the_number(void)
{
    int number, rc;

    if ((rc = read_number(&number)) != OK)
        return rc;

    node_t *head = NULL;

    if ((rc = fill_the_list(&head, number)) != OK)
    {
        free_linked_list(head);
        return rc;
    }

    square_the_number(head);

    print_linked_list(head);
    free_linked_list(head);

    return OK;
}

int dividing_number_without_rem(void)
{
    int first_numb, rc;

    if ((rc = read_number(&first_numb)) != OK)
        return rc;

    node_t *first_head = NULL;

    if ((rc = fill_the_list(&first_head, first_numb)) != OK)
    {
        free_linked_list(first_head);
        return rc;
    }

    int second_numb;

    if ((rc = read_number(&second_numb)) != OK)
    {
        free_linked_list(first_head);
        return rc;
    }

    node_t *second_head = NULL;

    if ((rc = fill_the_list(&second_head, second_numb)) != OK)
    {
        free_linked_list(first_head);
        free_linked_list(second_head);
        return rc;
    }

    node_t *res_head = NULL;

    if ((rc = division_of_two_numbers(first_head, second_head, &res_head)) != OK)
    {
        free_linked_list(res_head);
        return rc;
    }

    print_linked_list(res_head);
    free_linked_list(res_head);

    return OK;
}

node_t *multiply_numbers(node_t *first_head, node_t *second_head)
{
    node_t *long_list_elem, *short_list_elem, *res_head;

    if (length_list(first_head) >= length_list(second_head))
    {
        res_head = first_head;
        long_list_elem = first_head;
        short_list_elem = second_head;
    }
    else
    {
        res_head = second_head;
        long_list_elem = second_head;
        short_list_elem = first_head;
    }

    while (short_list_elem)
    {
        long_list_elem->power += short_list_elem->power;
        short_list_elem = short_list_elem->next;
        long_list_elem = long_list_elem->next;
    }

    return res_head;
}

int division_of_two_numbers(node_t *first_head, node_t *second_head, node_t **res_head)
{
    int first_number = extract_number_from_list(first_head);
    int second_number = extract_number_from_list(second_head);

    free_linked_list(first_head);
    free_linked_list(second_head);

    int res_div = first_number / second_number;

    if (!res_div)
        return EMPTY_LIST_ERROR;

    int rc = fill_the_list(res_head, res_div);
    return rc;
}
