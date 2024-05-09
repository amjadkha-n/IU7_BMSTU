#include "../inc/main.h"
#include <math.h>
void print_linked_list(node_t *head)
{
    while (head)
    {
        printf("%d ", head->power);
        head = head->next;
    }
    putchar('L');
    putchar('\n');
}

int read_number(int *number)
{
    if (scanf("%d", number) != 1)
        return READ_NUMBER_ERROR;

    return (*number <= 0) ? NEGATIVE_VALUE_ERROR : OK;
}

int fill_the_list(node_t **head, int number)
{
    node_t *end_elem;
    int base_degree = 2;

    while (number > 1)
    {   
        end_elem = insert_item_to_list(head);
        
        if (!end_elem)
        {
            free_linked_list(*head);
            return ALIGNMENT_ERROR;
        }
        
        for (; number % base_degree == 0; number /= base_degree)
        {
            end_elem->power++;
        }

        do
        {
            base_degree++;
        } while (check_if_prime(base_degree) != OK);
    }

    return OK;
}

node_t *insert_item_to_list(node_t **head)
{
    node_t *new_elem = malloc(sizeof(node_t));

    if (!new_elem)
    {
        free_linked_list(*head);
        return NULL;
    }

    new_elem->power = 0;
    new_elem->next = NULL;

    while (*head != NULL)
    {
        head = &(*head)->next;
    }

    *head = new_elem;

    return new_elem;
}


void free_linked_list(node_t *head)
{
    while (head)
    {
        node_t *temp = head;
        head = head->next;
        free(temp);
    }
}

#include "../inc/main.h"

int check_if_prime(int number)
{
    if (number < 2)
    {
        return CUSTOM_ERROR;
    }

    for (int i = 2; i * i <= number; i++)
    {
        if (number % i == 0)
        {
            return CUSTOM_ERROR;
        }
    }

    return OK;
}

void square_the_number(node_t *head)
{
    while (head)
    {
        head->power *= head->power;
        head = head->next;
    }
}

int length_list(node_t *head)
{
    int len = 0;

    for (; head; len++, head = head->next);

    return len;
}

int extract_number_from_list(node_t *head)
{
    int number = 1, base_degree = 2;

    while (head)
    {
        number *= (int)pow(base_degree, head->power);
        
        while (check_if_prime(++base_degree) != OK);
        
        head = head->next;
    }

    return number;
}
