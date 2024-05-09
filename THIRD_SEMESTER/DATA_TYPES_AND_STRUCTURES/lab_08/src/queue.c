#include "../inc/queue.h"

#include <stdio.h>
#include <stdlib.h>

// Function to create a new node with given data
node_t *create_node(int data) 
{
    node_t *node = malloc(sizeof(node_t));
    
    if (node)
    {
        // Initialize node data and set next pointer to NULL
        node->data = data;
        node->next = NULL;
    }
    
    return node;
}

// Function to push a new node to the back of the queue
queue_t* push_back(queue_t *queue, node_t *node)
{
    // Check if the queue is empty
    if (!queue->top)
    {
        // If empty, set both top and bot pointers to the new node
        queue->top = node;
        queue->bot = node;
    }
    else
    {
        // If not empty, add the new node to the back of the queue and update bot pointer
        queue->bot->next = node;
        queue->bot = queue->bot->next;
    }

    return queue;
}

// Function to pop the front node from the queue
queue_t* pop_front(queue_t *queue)
{
    // Store the next node after the current top
    node_t *temp = queue->top->next;

    // Free the memory allocated for the current top node
    free(queue->top);

    // Update the top pointer to the next node
    queue->top = temp;

    // Return the updated queue
    return queue;
}

// Function to initialize a queue by setting both top and bot pointers to NULL
void init_queue(queue_t *queue)
{
    queue->bot = NULL;
    queue->top = NULL;
}

// Function to free the memory allocated for all nodes in the queue
void free_queue(queue_t *queue)
{
    // Iterate through the queue and free each node
    while (queue->top)
    {
        // Store the current top node
        node_t *temp = queue->top;
        // Update the top pointer to the next node
        queue->top = queue->top->next;
        // Free the memory allocated for the current node
        free(temp);
    }
}

// Function to print the data of all nodes in the queue
void print_queue(queue_t queue)
{
    // Iterate through the queue and print the data of each node
    while (queue.top)
    {
        // Print the data of the current top node
        printf("%d ", queue.top->data);
        // Update the top pointer to the next node
        queue.top = queue.top->next;
    }
}
