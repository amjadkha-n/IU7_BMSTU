// Пользователь вводит целые числа. Признаком окончания ввода считается ввод 0.
// Создать линейный односвязный список, элементы добавляются в начало списка.
// Ноль не попадает в список. Подсчитать количество минимальных элементов
// списка. Вставить найденное число в список после первого минимума. Память
// выделяется динамически. Вывести полученный список на экран. Числа выводятся в
// строку через пробел (используется спецификатор "%d ").
// Приглашение к вводу выдавать не нужно.
// При возникновении какой-либо ошибки выдать сообщение "ERROR: N", где N
// равно 1 в случае ошибок ввода, 2 в случае ошибок выделения памяти, 3 в случае,
// если результирующий список пуст.
// В конце работы программы вся динамически выделенная память должна быть
// освобождена.
// Пример
// Ввод
// 5 1 5 1 5 1 0
// Вывод
// 1 3 5 1 5 1 5
// Ввод
// 4 4 4 0
// Вывод
// 4 3 4 4
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
int count_min(Node *head)
{
    if (head == NULL)
    {
        printf("Error: 3\n");
        exit(3);
    }
    int min = head->data;
    int count = 1;
    while (head->next != NULL)
    {
        head = head->next;
        if (head->data < min)
        {
            min = head->data;
            count = 1;
        }
        else if (head->data == min)
        {
            count++;
        }
    }
    return count;
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
    int count_minimum = count_min(head);
    Node *temp = head;
    while (temp != NULL)
    {
        if (temp->data == head->data)
        {
            insert_front(&(temp->next), count_minimum);
            break;
        }
    }
    print_list(head);
    free_list(head);
    return 0;
}