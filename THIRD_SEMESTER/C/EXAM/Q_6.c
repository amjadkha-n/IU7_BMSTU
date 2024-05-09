// Пользователь вводит целое положительное число. С помощью очереди развернуть
// число. Память выделяется динамически. Вывести число на экран. Цифры выводятся
// в строку (используется спецификатор "%d ").
// Приглашение к вводу выдавать не нужно.
// При возникновении какой-либо ошибки выдать сообщение "ERROR: N", где N
// равно 1 в случае ошибок ввода, 2 в случае ошибок выделения памяти.
// В конце работы программы вся динамически выделенная память должна быть
// освобождена.
// Пример
// Ввод
// 12345
// Вывод
// 54321
// Ввод
// -123
// Вывод
// ERROR: 1
// Ввод
// 0
// Вывод
// ERROR: 2

#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in a linked list
typedef struct Node
{
    int data;            // Data stored in the node
    struct Node* next;   // Pointer to the next node in the linked list
} Node;

// Define a structure for a queue, which uses linked list nodes
typedef struct
{
    Node* front;          // Pointer to the front (head) of the queue
    Node* rear;           // Pointer to the rear (tail) of the queue
} Queue;

// Function to enqueue (insert) a new element into the queue
void enqueue(Queue* q, int value)
{
    Node* new_node = (Node*)malloc(sizeof(Node));  // Allocate memory for a new node
    if (new_node == NULL)
    {
        printf("ERROR: 2\n");  // Print an error message if memory allocation fails
        exit(2);               // Exit the program with an error code 2 (memory allocation error)
    }
    new_node->data = value;    // Set the data of the new node to the given value
    new_node->next = NULL;     // Initialize the next pointer of the new node to NULL

    if (q->front == NULL)
    {
        q->front = q->rear = new_node;  // If the queue is empty, set both front and rear to the new node
    }
    else
    {
        q->rear->next = new_node;       // If the queue is not empty, link the current rear to the new node
        q->rear = new_node;             // Update the rear to be the new node
    }
}

// Function to dequeue (remove) an element from the front of the queue
int dequeue(Queue* q)
{
    if (q->front == NULL)
    {
        printf("ERROR: 2\n");  // Print an error message if trying to dequeue from an empty queue
        exit(2);               // Exit the program with an error code 2 (empty queue error)
    }

    Node* temp = q->front;      // Create a temporary pointer to the front node
    int value = temp->data;     // Retrieve the data from the front node

    q->front = temp->next;      // Move the front pointer to the next node in the queue
    if (q->front == NULL)
    {
        q->rear = NULL;          // If the queue becomes empty after dequeue, update the rear to NULL
    }

    free(temp);                  // Free the memory of the dequeued node
    return value;                // Return the dequeued value
}

// Function to reverse a number using a queue and print the reversed digits
void reverseAndPrint(int num)
{
    Queue q = {NULL, NULL};     // Initialize an empty queue

    while (num > 0)
    {
        enqueue(&q, num % 10);   // Enqueue the last digit of the number
        num /= 10;               // Remove the last digit from the number
    }
    if (q.front == NULL)
    {
        printf("Error: 3\n");
        exit(3);
    }

    while (q.front)
    {
        printf("%d", dequeue(&q));  // Dequeue and print each digit to reverse the order
    }

    printf("\n");
}

// Main function
int main()
{
    Node *head = NULL;
    int input;
    if (scanf("%d", &input) != 1 || getchar() != '\n' || input < 0)
    {
        printf("Error: 1\n");
        exit(1);
    }
    reverseAndPrint(input);
    
    return 0;
}


