// Пользователь вводит целые числа. Признаком окончания ввода считается ввод 0.
// Создать линейный односвязный список. Элементы добавляются в конец списка.
// Развернуть список (без создания копий). Числа выводятся в строку через пробел
// (используется спецификатор "%d ").
// Приглашение к вводу выдавать не нужно.
// При возникновении какой-либо ошибки выдать сообщение "ERROR: N", где N
// равно 1 в случае ошибок ввода, 2 в случае ошибок выделения памяти, 3 в случае,
// если результирующий список пуст.
// В конце работы программы вся динамически выделенная память должна быть
// освобождена.
// Пример
// Ввод
// -1 2 3 -4 -5 6 0
// Вывод
// 6 -5 -4 3 2 -1
// Ввод
// D
// Вывод
// ERROR: 1
// Ввод
// 0
// Вывод
#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in the linked list
struct Node 
{
    int data;            // Data of the node
    struct Node* next;   // Pointer to the next node in the list
};

// Function to add a new node to the end of the linked list
void append(struct Node** head, int value)
{
    // Allocate memory for a new node
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    // Check if memory allocation was successful
    if (new_node == NULL)
    {
        printf("ERROR: 2\n");  // Error message for memory allocation failure
        exit(2);               // Exit the program with error code 2
    }

    // Set the data and next pointer of the new node
    new_node->data = value;
    new_node->next = NULL;

    // Check if the list is empty and update the head pointer accordingly
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        // Traverse the list to find the last node and append the new node
        struct Node* temp = *head;  // Temporary pointer to traverse the list
        while (temp->next != NULL)
        {
            temp = temp->next;  // Move to the next node
        }
        temp->next = new_node;  // Append the new node to the end of the list
    }
}


// Function to reverse the linked list in-place
void reverse(struct Node** head)
{
    struct Node* prev = NULL;   // Pointer to the previous node during reversal
    struct Node* current = *head;  // Pointer to the current node during reversal
    struct Node* next = NULL;   // Pointer to the next node during reversal

    // Traverse the list and reverse the next pointers of each node
    while (current != NULL)
    {
        next = current->next;    // Save the next node
        current->next = prev;    // Reverse the next pointer
        prev = current;          // Move to the next node
        current = next;          // Move to the saved next node
    }

    // Update the head pointer to point to the new first node
    *head = prev;
}
void printList(struct Node* head) 
{
    // Traverse the list and print the data of each node
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
}
// Function to free the allocated memory for the linked list
void freeList(struct Node* head)
{
    struct Node* temp;

    // Traverse the list and free the memory of each node
    while (head != NULL)
    {
        temp = head;            // Save the current node
        head = head->next;      // Move to the next node
        free(temp);             // Free the saved node
    }
}


// Main function
int main()
{
    struct Node* head = NULL;  // Head pointer of the linked list
    int input;

    // Read input from the user until 0 is entered
    while (1)
    {
        // Check if the input is a valid integer
        if (scanf("%d", &input) == 1) {
            // Break the loop if 0 is entered
            if (input == 0)
            {
                break;
            }
            else
            {
                // Add the input value to the end of the linked list
                append(&head, input);
            }
        }
        else
        {
            printf("ERROR: 1\n");  // Error message for invalid input
            freeList(head);       // Free the allocated memory
            return 1;              // Exit the program with error code 1
        }
    }

    // Check if the list is empty
    if (head == NULL)
    {
        printf("ERROR: 3\n");  // Error message for an empty list
        return 3;              // Exit the program with error code 3
    }

    // Reverse the linked list in-place
    reverse(&head);

    // Print the reversed list
    printList(head);

    // Free the allocated memory
    freeList(head);

    return 0;  // Exit the program successfully
}
