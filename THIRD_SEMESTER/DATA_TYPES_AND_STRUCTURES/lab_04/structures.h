/**
 * @file structures.h
 * @brief Definition of structures used in the program.
 */

#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

/**
 * @brief Boolean type definition.
 */
typedef enum boolean
{
    false = 0,
    true = 1
} bool;

/**
 * @brief Structure representing the maze.
 */
typedef struct maze
{
    char **matrix; /**< 2D array representing the maze. */
    int x;        /**< Number of columns in the maze. */
    int y;        /**< Number of rows in the maze. */
    int i_enter;  /**< Entrance row index. */
    int j_enter;  /**< Entrance column index. */
} maze_t;

/**
 * @brief Structure representing an element in the linked list.
 */
typedef struct list_element
{
    int i;                       /**< Row index. */
    int j;                       /**< Column index. */
    int direction;               /**< Direction. */
    struct list_element *next_elem; /**< Pointer to the next element in the list. */
} list_element_t;

/**
 * @brief Structure representing a linked list.
 */
typedef struct list
{
    list_element_t *ptr; /**< Pointer to the first element in the list. */
} stack_list_t;

/**
 * @brief Structure representing an element in the array-based stack.
 */
typedef struct array_elem
{
    int i;         /**< Row index. */
    int j;         /**< Column index. */
    int direction; /**< Direction. */
} array_element_t;

/**
 * @brief Structure representing an array-based stack.
 */
typedef struct array
{
    array_element_t *ptr; /**< Pointer to the array of elements. */
    int size;            /**< Size of the stack. */
} stack_array_t;

#endif
