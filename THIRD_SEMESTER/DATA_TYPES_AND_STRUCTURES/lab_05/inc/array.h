#ifndef ARRAY_H
#define ARRAY_H

#include"app.h"
#include "timemem.h"
/**
 * @brief Simulates the processing of requests in a system with two queues.
 *
 * @param n Number of requests to be processed.
 * @param interval Interval for displaying application processing information.
 * @param t1 Structure representing time parameters for the first queue.
 * @param t2 Structure representing time parameters for the second queue.
 * @param t3 Structure representing time parameters for the first queue application processing.
 * @param t4 Structure representing time parameters for the second queue application processing.
 */
void sd_array(int n, int interval, times_r t1, 
              times_r t2, times_r t3, times_r t4);
/**
 * @brief Pushes an element into the queue.
 *
 * @param queue Pointer to the queue structure.
 * @param c_elem Character element to be pushed into the queue.
 */
void queuearray_push(queue_r *queue, char c_elem);

/**
 * @brief Pops an element from the queue.
 *
 * @param queue Pointer to the queue structure.
 * @return char Popped character element.
 */
char queuearray_pop(queue_r *gueue);
/**
 * @brief Prints the elements of the queue.
 *
 * @param queue Pointer to the queue structure.
 */
void queuearray_print(queue_r *queue);

#endif // ARRAY_H
