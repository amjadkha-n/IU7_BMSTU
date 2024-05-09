// Пользователь вводит целые числа. Признаком окончания ввода считается ввод 0.
// Создать линейный односвязный список, элементы добавляются в начало списка.
// Ноль не попадает в список. Найти максимальное число в списке. Удалить все
// максимальные элементы. Память выделяется динамически. Вывести полученный
// список на экран. Числа выводятся в строку через пробел (используется
// спецификатор "%d ").
// Приглашение к вводу выдавать не нужно.
// При возникновении какой-либо ошибки выдать сообщение "ERROR: N", где N
// равно 1 в случае ошибок ввода, 2 в случае ошибок выделения памяти, 3 в случае,если результирующий список пуст.
// В конце работы программы вся динамически выделенная память должна быть
// освобождена.
// Пример
// Ввод
// 5 3 5 2 5 1 0
// Вывод
// 1 2 3
// Ввод
// 1 5 2 5 3 5 5 0
// Вывод
// 3 2 1
// Ввод
// 4 d
// Вывод
// ERROR: 1
// Ввод
// 0
// Вывод
// ERROR: 3

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void insert_front(Node **head, int value)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        printf("Error: 2\n");
        exit(2);
    }

    new_node->data = value;
    new_node->next = *head;
    *head = new_node;
}

void print_list(Node *head)
{
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}
void free_list(Node *head)
{
    Node *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}


int remove_max(Node **head)
{
    if (head == NULL)
    {
        printf("Error: 3\n");
        exit(3);
    }

    // Initialize variables to store the maximum value, current node, and the previous node.
    int max_value = (*head)->data;  // Initialize max_value with the value of the first node.
    Node *current = *head;          // Initialize current with the head of the list.
    Node *previous = NULL;          // Initialize previous as NULL since there is no previous node for the first node.

    // Iterate through the list to find the maximum value.
    while (current != NULL)
    {
        // Check if the data of the current node is greater than the current max_value.
        if (current->data > max_value)
        {
            // Update max_value with the data of the current node.
            max_value = current->data;
        }

        // Move to the next node in the list.
        current = current->next;
    }

    // Reset current to the head of the list for the removal phase.
    current = *head;

    // Iterate through the list to remove all occurrences of the maximum value.
    while (current != NULL)
    {
        // Check if the data of the current node is equal to the max_value.
        if (current->data == max_value)
        {
            // Check if the current node is the first node in the list.
            if (previous == NULL)
            {
                // Update the head to skip the current node.
                *head = current->next;
            }
            else
            {
                // Update the next pointer of the previous node to skip the current node.
                previous->next = current->next;
            }

            // Free the memory allocated for the current node.
            free(current);

            // Move current back to the head for the next iteration.
            current = *head;
        }
        else
        {
            // Update previous to the current node, and move to the next node in the list.
            previous = current;
            current = current->next;
        }
    }

    // Return the maximum value that was removed from the list.
    return max_value;
}


int main()
{
    Node *head = NULL;
    int input;
    while (1)
    {
        if (scanf("%d", &input) != 1)
        {
            printf("Error: 1\n");
            return 1;
        }
        else
        {
            if (input == 0)
            {
                break;
            }
            else
            {
                insert_front(&head, input);
            }
        }
    }
    remove_max(&head);
    print_list(head);
    free_list(head);
    return 0;
}