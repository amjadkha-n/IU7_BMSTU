// Во всех задачах исходные данные хранятся в текстовом файле. 
// После чтения из файла элементы помещаются в конем списка. 
// Имя файла в программу передается через параметры командной строки.
// В линейном односвязном списке хранятся целые числа. 
// Перед максимальным элементом вставить новый элемент, равный количеству чисел, заканчивающихся на цифру 8.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
} Node;

// void insertFront(Node** head, int value)
// {
//     Node* newNode = (Node*)malloc(sizeof(Node));
//     if (newNode == NULL)
//     {
//         fprintf(stderr, "Memory allocation error\n");
//         exit(2);
//     }

//     newNode->data = value;
//     newNode->next = *head;
//     *head = newNode;
// }

void insert_end(Node **head, int value)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        exit(2);
    }
    new_node->data = value;
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
void printList(Node* head)
{
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void freeList(Node* head)
{
    Node* temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int countDigitsEndingWith8(Node* head)
{
    int count = 0;
    while (head != NULL)
    {
        if (head->data % 10 == 8)
        {
            count++;
        }
        head = head->next;
    }
    return count;
}

void insertBeforeMax(Node** head)
{
    // Check if the linked list is empty
    if (*head == NULL)
    {
        return; // If empty, nothing to insert
    }

    // Initialize pointers for tracking the maximum node and its predecessor
    Node* current = *head;
    Node* maxNode = *head;
    Node* prevMaxNode = NULL;

    // Find the maximum value node in the linked list
    while (current->next != NULL)
    {
        // Check if the next node has a greater value than the current maxNode
        if (current->next->data > maxNode->data)
        {
            // Update maxNode and its predecessor
            maxNode = current->next;
            prevMaxNode = current;
        }
        // Move to the next node in the linked list
        current = current->next;
    }

    // Calculate the count of numbers ending with 8 in the linked list
    int count8 = countDigitsEndingWith8(*head);

    // Allocate memory for the new node to be inserted
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(2); // Exit the program if memory allocation fails
    }

    // Set the data and next pointer for the new node
    newNode->data = count8;
    newNode->next = maxNode;

    // Check if the maxNode is the head of the linked list
    if (prevMaxNode == NULL)
    {
        // If maxNode is the head, update head to point to the new node
        *head = newNode;
    }
    else
    {
        // If maxNode is not the head, update the predecessor's next pointer to the new node
        prevMaxNode->next = newNode;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to open file %s\n", argv[1]);
        return 1;
    }

    Node* head = NULL;
    int value;

    // Read integers from the file and construct the linked list
    while (fscanf(file, "%d", &value) == 1)
    {
        // insertFront(&head, value);
        insert_end(&head, value);
    }

    // Insert a new element before the maximum element
    insertBeforeMax(&head);

    // Print the updated list
    printList(head);

    // Free allocated memory
    freeList(head);

    fclose(file);
    return 0;
}
