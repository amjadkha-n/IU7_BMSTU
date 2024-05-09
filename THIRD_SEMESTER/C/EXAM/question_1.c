#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insertAtBeginning(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
}

int findMax(struct Node* head) {
    int max = head->data;
    while (head != NULL) {
        if (head->data > max) {
            max = head->data;
        }
        head = head->next;
    }
    return max;
}

int countNumbersEndingIn8(struct Node* head) {
    int count = 0;
    while (head != NULL) {
        if (head->data % 10 == 8) {
            count++;
        }
        head = head->next;
    }
    return count;
}

void performTask(char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct Node* head = NULL;
    int value;
    while (fscanf(file, "%d", &value) == 1) {
        insertAtBeginning(&head, value);
    }

    fclose(file);

    int maxElement = findMax(head);
    int countEndingIn8 = countNumbersEndingIn8(head);

    struct Node* current = head;
    struct Node* prev = NULL;

    // Find the maximum element in the list
    while (current != NULL && current->data != maxElement) {
        prev = current;
        current = current->next;
    }

    // Insert a new element before the maximum element
    if (prev != NULL) {
        insertAtBeginning(&(prev->next), countEndingIn8);
    } else {
        // If max element is at the beginning
        insertAtBeginning(&head, countEndingIn8);
    }

    // Print the updated list
    printf("Updated list after inserting count of numbers ending in 8 before the maximum element:\n");
    current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }

    // Free allocated memory
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char* fileName = argv[1];
    performTask(fileName);

    return 0;
}
