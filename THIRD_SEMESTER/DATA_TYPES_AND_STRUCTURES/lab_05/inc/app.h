#ifndef APP_H
#define APP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
/**
 * @brief ANSI color codes for console text.
 */
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET    "\x1b[0m"

/**
 * @brief Maximum length of the queue.
 */
#define MAXLENQUEUE       10000

/**
 * @brief A small value for epsilon comparisons.
 */
#define EPS                 1e-9

/**
 * @brief Maximum length for some arrays.
 */
#define MAXLEN             100

/**
 * @brief Processor speed in GHz.
 */
#define GHZ                  1.9

/**
 * @brief Number of iterations.
 */
#define ITER               10000
/**
 * @brief Boolean values.
 */
#define TRUE                   1
#define FALSE                  0

/**
 * @brief Return codes for functions.
 */
#define OK                     0
#define INPUT_ERR             -1
#define FILE_OPEN_ERR         -2
#define FILE_READ_ERR         -3
#define DONT_INT_NUM_CHOICE   -4
#define INV_NUM_CHOICE        -5

typedef char queuetype;
/**
 * @brief Structure representing a queue.
 */
typedef struct queue
{
    char name[30];      /**< Queue Name */
    void* low;          /**< Address of the lower border */
    void* up;           /**< The address of the upper boundary */
    void* p_in;         /**< A pointer to the last element */
    void* p_out;        /**< A pointer to the "first to exit" element */
    int count_len;      /**< Number of elements */
    size_t size;        /**< The size of the data type */
    int count_req;      /**< Number of requests */
    int sum_len;        /**< Total queue length */
    int tmp_len;        /**< Current queue length */
    int sum_time;       /**< Total time */
    int out_req;        /**< Number of exit requests */
    int in_req;         /**< Number of login requests */
} queue_r;
/**
 * @brief Structure representing a node in the queue.
 */
typedef struct node
{
    char inf;           /**< Information about the element */
    struct node *next;  /**< A pointer to the next node */
} node_r;

/**
 * @brief Structure representing time range.
 */
typedef struct times
{
    double min;         /**< Minimum time */
    double max;         /**< Maximum time */
} times_r;

#endif // APP_H
