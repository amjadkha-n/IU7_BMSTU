// Вводится информация об окружностях - координаты центра x, y и радиус r. 
// Требуется занести окружности в список(новая окружность вставляется в конец). 
// По введенному списку найти окружность с наименьшим радиусом(если таких несколько,
//  использовать последнюю из них) и ПЕРЕД ней вставить новую окружность с такими же координатами x, y и 
//  радиусом, равным среднему арифметическому всех радиусов в списке. x, y, r - вещественные. Для вывода используется строка “%f %f %f\n”.
// input:
// 1 1 1
// 0 0 8
// 2 2 3
// outptu:
// 1 1 4
// 1 1 1
// 0 0 8
// 2 2 3
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    double x, y, r;
    struct Node *next;
} Node;

void insert_end(Node **head, double x, double y, double r)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    new_node->x = x;
    new_node->y = y;
    new_node->r = r;
    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        Node *temp = *head;
        while(temp->next != NULL)
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
        printf("%f %f %f \n", head->x, head->y, head->r);
        head = head->next;
    }
    printf("\n");
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


Node *find_smallest_radius(Node *head)
{
    Node *smallest = NULL;
    Node *current = head;

    while (current != NULL)
    {
        if (smallest == NULL || current->r < current->r)
        {
            smallest = current;
        }
        current = current->next;
    }
    return smallest;
}

double radius_mean(Node *head)
{
    Node *current = head;
    double sum = 0.0;
    int count = 0;
    while (current != NULL)
    {
        sum += current->r;
        count ++;
        current = current->next;
    }
    if (count == 0)
    {
        return 0.0;
    }
    
    return sum / count;
} 

void insert_front(Node **head, Node *smallest_node, double mean_radius)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    new_node->x = smallest_node->x;
    new_node->y = smallest_node->y;
    new_node->r = mean_radius;
    new_node->next = smallest_node;

    if (smallest_node == *head)
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

int main()
{
    Node *head = NULL;
    double x, y, r;
    while (1)
    {
        if (scanf("%lf %lf %lf", &x, &y, &r) != 3)
        {
            break;
        }
        insert_end(&head, x, y, r);
    }
    Node *smallest_node = find_smallest_radius(head);
    if (smallest_node != NULL)
    {
        double radius_meann = radius_mean(head);
        insert_front(&head, smallest_node, radius_meann);
    }

    print_list(head);
    free_list(head);
    return 0;
}