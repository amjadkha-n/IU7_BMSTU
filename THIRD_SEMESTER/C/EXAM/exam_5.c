// На вход идут числа тройками: номер вагона, количество мест и количество людей (int). Числа на входе не проверяются. 
// После ввода полностью заполненные вагоны (кол-во мест = кол-во людей) перемещаются в начало списка. Это выводится на экран ("%d %d %d\n") . 
// В случае ошибки выделения памяти или пустого списка выводится "Error\n"
// Пример:
// На вход:
// 1 2 3
// 2 10 10
// 3 4 4
// 4 5 6
// На выход:
// 3 4 4
// 2 10 10
// 1 2 3
// 4 5 6
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int a, b, c;
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
    if (*head == NULL)
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

void insert_front(Node **head)
{
    Node *current = *head;
    Node *previous = NULL;
    while (current != NULL)
    {
        if (current->b == current->c)
        {
            Node *temp = current;
            if (previous != NULL)
            {
                previous->next = current->next;
                current = current->next;

                temp->next = *head;
                *head = temp;
            }
            else
            {
                current = current->next;
            }
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
}

int main()
{
    Node *head = NULL;
    int a, b, c;
    while (scanf("%d %d %d", &a, &b, &c) == 3)
    {
        insert_end(&head, a, b, c);
    }
    insert_front(&head);
    print_list(head);
    free_list(head);
    return 0;
}