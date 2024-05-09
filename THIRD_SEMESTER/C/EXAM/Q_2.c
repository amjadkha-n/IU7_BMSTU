// Пользователь вводит целые числа. Признаком окончания ввода считается ввод 0.
// Создать два линейных односвязных списка: в первый помешать только
// положительные числа, во второй - отрицательные. Ноль не попадает ни в один
// список. Элементы добавляются в начало списка. После окончания ввода соединить
// два списка в один, причем сначала должны расположиться положительные
// элементы, после - отрицательные. Память выделяется динамически. Вывести
// полученный список на экран. Числа выводятся в строку через пробел
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
// 6 3 2 -5 -4 -1
// Ввод
// D
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
        printf("Error: 2");
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
}

void free_list(Node *head)
{
    Node *current;
    while(head != NULL)
    {
        current = head;
        head = head->next;
        free(current);       
    }
}

Node *merge_list(Node *positive_list, Node *negative_list)
{
    if (positive_list == NULL)
    {
        return negative_list;
    }

    Node *current = positive_list;

    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = negative_list;
    return positive_list;
}

int main()
{
    Node *positive_list = NULL;
    Node *negative_list = NULL;
    int input;

    while (1)
    {
        if (scanf("%d", &input) != 1)
        {
            printf("Exit: 1");
            free_list(positive_list);
            free_list(negative_list);
            return 1;
        }
        else
        {
            if (input == 0)
            {
                break;
            }
            else if(input > 0)
            {
                insert_front(&positive_list, input);
            }
            else
            {
                insert_front(&negative_list, input);
            }
        }
    }
    if (positive_list == NULL && negative_list == NULL)
    {
        printf("Exit: 3");
        return 3;
    }
    Node *merged_list = merge_list(positive_list, negative_list);
    print_list(merged_list);
    free_list(merged_list);
    return 0;
}