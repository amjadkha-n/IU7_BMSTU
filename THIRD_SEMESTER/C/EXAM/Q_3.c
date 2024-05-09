// Пользователь вводит строки, длина которых не превосходит 80 символов. Строка
// со значением "The end" является последней (регистр важен). Очередная
// выделенная строка помещается в начала линейного односвязного списка. Узел
// списка хранит указатель на строку, память под строку выделяется динамически.
// Строка "The end" в список не помещается. После окончания ввод программа
// выводит строки в каждом узле на экран. Строки выводятся в одинарных кавычках
// через пробел (используется спецификатор "'%s' ").
// Приглашение к вводу выдавать не нужно.
// В конце работы программы вся динамически выделенная память должна быть
// освобождена.
// Пример
// Ввод
// Peter
// is
// name
// My
// The end
// Вывод
// 'My' 'name' 'is' 'Peter'
// Ввод
// The end
// Вывод
// Empty list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 80

typedef struct Node
{
    char* data;
    struct Node* next;
} Node;

void insertFront(Node** head, char* value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        exit(2);
    }

    newNode->data = strdup(value);
    if (newNode->data == NULL)
    {
        exit(2);
    }

    newNode->next = *head;
    *head = newNode;
}

void printList(Node* head)
{
    if (head == NULL)
    {
        printf("Empty list\n");
        return;
    }

    while (head != NULL)
    {
        printf("'%s' ", head->data);
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
        free(temp->data);
        free(temp);
    }
}

int main()
{
    Node* head = NULL;
    char input[MAX_STRING_LENGTH + 1]; // +1 for null terminator

    while (1)
    {
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            freeList(head);
            return 1;
        }

        // Remove newline character from the input
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "The end") == 0)
        {
            break;
        }

        insertFront(&head, input);
    }

    printList(head);

    // Free allocated memory
    freeList(head);

    return 0;
}
