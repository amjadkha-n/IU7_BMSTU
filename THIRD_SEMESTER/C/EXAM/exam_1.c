// Вводятся тройки чисел в конец списка.

// Если 2 и 3 элементы тройки одинаковые, поместить их в начало, причем в порядке ввода

// Ввод до первой ошибки.

// Ввод
// 1 2 3
// 2 2 2
// 3 4 5
// 4 5 5
// а

// Выход
// 2 2 2
// 4 5 5
// 1 2 3
// 3 4 5
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

void print_list (Node *head)
{
    while (head != NULL)
    {
        printf("%d %d %d\n", head->a, head->b, head->c);
        head = head->next;
    }
}

void free_list (Node *head)
{
    Node *temp = NULL;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int count_values(Node *head)
{
    int count =  (head->a == head->b) + (head->a == head->c) + (head->b == head->c); 
    return count;
}
void insert_front(Node **head)
{
    Node *current = *head;  // Pointer to traverse the list
    Node *previous = NULL;  // Pointer to keep track of the previous node
    int count = 0;          // Counter for the number of equal values in a node
    while (current != NULL)  // Loop through the linked list
    {
        count = count_values(current);  // Count equal values in the current node
        if (count >= 1)  // If there are at least two equal values in the node
        {
            Node *temp = current;  // Temporary pointer to the current node
            if (previous != NULL)  // If there is a previous node
            {
                previous->next = current->next;  // Skip the current node in the list
                current = current->next;  // Move to the next node

                temp->next = *head;  // Insert the current node at the front
                *head = temp;  // Update the head to point to the new front node
            }
            else
            {
                current = current->next;  // Skip the current node without changing pointers
            }
        }
        else
        {
            previous = current;  // Update the previous pointer
            current = current->next;  // Move to the next node
        }
    }
}

int main()
{
    Node *head = NULL;
    int a, b, c;
    while (1)
    {
        if (scanf("%d %d %d", &a, &b, &c) != 3)
        {
            break;
        }
        insert_end(&head, a, b, c);
    }
    insert_front(&head);
    print_list(head);
    free_list(head);
    return 0;
}