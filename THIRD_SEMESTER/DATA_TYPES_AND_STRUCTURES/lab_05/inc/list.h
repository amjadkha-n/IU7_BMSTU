#ifndef LIST_H
#define LIST_H

#include "app.h"
#include "timemem.h"
#include "io.h"
/**
 * @brief Creates a new node with the given element.
 *
 * @param c The element to be stored in the new node.
 * @return node_r* A pointer to the newly created node.
 */
node_r* createelem(queuetype c);
/**
 * @brief Adds a new node to the front of the linked list.
 *
 * @param head The current head of the linked list.
 * @param elem The node to be added to the front.
 * @return node_r* The new head of the linked list.
 */
node_r* pushfront(node_r *head, node_r *elem);
/**
 * @brief Removes and returns the node from the front of the linked list.
 *
 * @param head Pointer to the pointer to the head of the linked list.
 * @return node_r* The node removed from the front of the linked list.
 */
node_r* popfront(node_r **head);

/**
 * @brief Removes and returns the node from the end of the linked list.
 *
 * @param head Pointer to the pointer to the head of the linked list.
 * @return node_r* The node removed from the end of the linked list.
 */
node_r* popend(node_r **head);
/**
 * @brief Frees all nodes in the linked list.
 *
 * @param head The head of the linked list.
 */
void freeall(node_r *head);
/**
 * @brief Simulates the operation of two queues using linked lists.
 *
 * @param n The number of iterations for the simulation.
 * @param interval The interval for displaying progress.
 * @param t1, t2, t3, t4 Timing parameters for the simulation.
 * @param flag Flag to indicate whether to print additional memory information.
 */
void sd_list(int n, int interval, times_r t1, 
              times_r t2, times_r t3, times_r t4, int flag);
/**
 * @brief Pushes a new element onto the queue represented by a linked list.
 *
 * @param queue Pointer to the head of the queue (linked list).
 * @param c The element to be pushed onto the queue.
 * @param user_memory Array to store used memory addresses.
 * @param user_count Pointer to the count of used memory addresses.
 * @param free_memory Array to store free memory addresses.
 * @param free_count Pointer to the count of free memory addresses.
 * @param second_use Pointer to the count of second-use memory addresses.
 * @return node_r* The updated head of the queue.
 */
node_r *queuelist_push(node_r *queue, queuetype c, node_r **user_memory,
                    int *user_count, node_r **free_memory,
                    int *free_count, int *second_use);
/**
 * @brief Pops an element from the end of the queue represented by a linked list.
 *
 * @param queue Pointer to the pointer to the head of the queue (linked list).
 * @return node_r* The removed node from the end of the queue.
 */
node_r *queuelist_pop(node_r **queue);
/**
 * @brief Prints the elements of the queue represented by a linked list.
 *
 * @param queue The head of the queue (linked list).
 */
void queuelist_print(node_r *queue);

#endif // LIST_H
