// На вход поступают тройки чисел: номер вагона поезда, количество мест и количество пассажиров. При вводе числа никак не проверяются. 
// Тройки хранятся в виде линейного односвязного списка. Ввод осуществляется до ошибки.
// Далее нужно удалить «неправильные тройки»: те, у которых неположительное количество мест или отрицательное количество пассажиров.
//  Удаление всех элементов - ошибка. При ошибке на экран выдается только сообщение “ERROR\n”
// Полученный список троек выводятся на экран.

// Входные данные:
// 1 2 10
// 5 7 0
// -1 1 0
// 10 0 1
// 8 3 -1
// a

// Выходные данные:
// 1 2 10
// 5 7 0
// -1 1 0
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int  a, b, c;
    struct Node *next;
} Node;

void insert_end(Node **head, int a, int b, int c)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (!new_node)
    {
        return;
    }
    new_node->a = a; 
    new_node->b = b; 
    new_node->c = c;
    new_node->next = NULL;
    if (!*head)
    {
        *head = new_node;
    }
    else
    {
        Node *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void print_list(Node *head)
{
    while (head != NULL)
    {
        printf("%d %d %d\n", head->a, head->b, head->c);
        head = head->next;
    }
    printf("\n");
}

void free_list(Node *head)
{
    Node *temp = NULL;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void remove_nodes(Node **head)
{
    Node *current = *head;  // Pointer to the current node in the linked list
    Node *previous = NULL;   // Pointer to the previous node in the linked list

    while (current != NULL)  // Loop through the linked list
    {
        if (current->b <= 0 || current->c < 0)  // Check if the current node has invalid values
        {
            if (previous == NULL)  // If the current node is the head of the list
            {
                *head = current->next;  // Update the head to skip the current node
            }
            else
            {
                previous->next = current->next;  // Skip the current node in the middle of the list
            }

            free(current);  // Free the memory of the current node with invalid values
        }
        else
        {
            previous = current;  // Update the previous pointer only if the current node is valid
        }

        current = current->next;  // Move to the next node in the linked list
    }
}

int main()
{
    Node *head = NULL;
    int x, y, r;
    while (1)
    {
        if (scanf("%d %d %d", &x, &y, &r) != 3)
        {
            break;
        }
        insert_end(&head, x, y, r);
    }
    remove_nodes(&head);
    print_list(head);
    free_list(head);
    return 0;
}