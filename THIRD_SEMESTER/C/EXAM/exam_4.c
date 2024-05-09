// Даны длина и ширина прямоугольников, вещественные. Вводятся в конец списка. Из них квадраты поместить в новый список.
//  Вывести сначала все прямоугольники, потом все квадраты.
// 5 7
// 5 5
// 20 3
// 4 4

// 5 7
// 20 3
// 5 5
// 4 4
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int length, width;
    struct Node *next;
} Node;

typedef struct SquareNode
{
    int side;
    struct SquareNode *next;
} SquareNode;

void insert_rectangle(Node **head, int length, int width)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
    {
        return;
    }
    new_node->length = length;
    new_node->width = width;
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

void insert_square(SquareNode **head, int side)
{
    SquareNode *new_node = (SquareNode *)malloc(sizeof(SquareNode));
    if (!new_node)
    {
        return;
    }
    new_node->side = side;
    new_node->next = NULL;

    if (!*head)
    {
        *head = new_node;
    }
    else
    {
        SquareNode *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void print_shapes(void *head, void (*print_function)(void *))
{
    print_function(head);
}

void print_rectangle(void *head)
{
    Node *current = (Node *)head;
    while (current != NULL)
    {
        printf("%d %d\n", current->length, current->width);
        current = current->next;
    }
}

void print_square(void *head)
{
    SquareNode *current = (SquareNode *)head;
    while (current != NULL)
    {
        printf("%d %d\n", current->side, current->side);
        current = current->next;
    }
}

void free_list(void *head, void (*free_function)(void *))
{
    free_function(head);
}

void free_rectangle_list(void *head)
{
    Node *temp = NULL;
    while (head != NULL)
    {
        temp = (Node *)head;
        head = ((Node *)head)->next;
        free(temp);
    }
}

void free_square_list(void *head)
{
    SquareNode *temp = NULL;
    while (head != NULL)
    {
        temp = (SquareNode *)head;
        head = ((SquareNode *)head)->next;
        free(temp);
    }
}

int main()
{
    Node *rectangles_head = NULL;
    SquareNode *squares_head = NULL;

    int length, width;
    while (scanf("%d %d", &length, &width) == 2)
    {

        if (length != width)
        {
            // insert_square(&squares_head, length);
            insert_rectangle(&rectangles_head, length, width);
        }
        else
        {
            insert_square(&squares_head, length);
        }
    }

    print_shapes(rectangles_head, print_rectangle);
    print_shapes(squares_head, print_square);

    // Free memory
    free_list(rectangles_head, free_rectangle_list);
    free_list(squares_head, free_square_list);

    return 0;
}
