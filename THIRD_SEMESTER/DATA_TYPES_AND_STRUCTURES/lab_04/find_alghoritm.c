#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "find_alghoritm.h"
#include "timer.h"
#include "structures.h"
#include "memory_operations.h"
#include "print.h"

#define NOT_DEADLOCK 0
#define DEADLOCK 1

#define TOP 1
#define RIGHT 2
#define BOTTOM 3
#define LEFT 4
#define NO_WAY 5

#define OK 0

#define MEMORY_ERROR 2
#define INVALID_FILE 3
#define STACK_EMPTY 7

#define LOG_FILE "log.txt"
/**
 * @brief Type of stack used in the algorithm.
 */
int __stack_type;
/**
 * @brief Total time spent during the algorithm execution.
 */
int64_t total_time;
/**
 * @brief Checks for available paths in the maze's corners.
 *
 * Checks for available paths in the maze's corners and updates the stack accordingly.
 *
 * @param maze         Pointer to the maze structure.
 * @param i            Current row position in the maze.
 * @param j            Current column position in the maze.
 * @param array        Pointer to the array-based stack.
 * @param list         Pointer to the list-based stack.
 * @param stack_size   Pointer to the stack size variable.
 * @param direction    Current direction of movement.
 * @return An integer code indicating the operation result.
 */
static int checking_for_corners(maze_t *const maze, int i, int j,
    stack_array_t *array, stack_list_t *list, int *stack_size, const int direction)
{
    int64_t start_time;

    if (i + 1 != maze->y)
    {
        if ((maze->matrix[i + 1][j] == ' ' || maze->matrix[i + 1][j] == '1') && direction != BOTTOM)
        {
            (*stack_size)++;
            maze->matrix[i][j] = '?';

            start_time = tick();

            if (push(array, list, i + 1, j, BOTTOM))
            {
                return MEMORY_ERROR;
            }

            total_time += tick() - start_time;
        }
    }

    if (i - 1 >= 0)
    {
        if ((maze->matrix[i - 1][j] == ' ' || maze->matrix[i - 1][j] == '1') && direction != TOP)
        {
            (*stack_size)++;
            maze->matrix[i][j] = '?';

            start_time = tick();

            if (push(array, list, i - 1, j, TOP))
            {
                return MEMORY_ERROR;
            }

            total_time += tick() - start_time;
        }
    }

    if (j + 1 != maze->x)
    {
        if ((maze->matrix[i][j + 1] == ' ' || maze->matrix[i][j + 1] == '1') && direction != RIGHT)
        {
            (*stack_size)++;
            maze->matrix[i][j] = '?';

            start_time = tick();

            if (push(array, list, i, j + 1, RIGHT))
            {
                return MEMORY_ERROR;
            }

            total_time += tick() - start_time;
        }
    }

    if (j - 1 >= 0)
    {
        if ((maze->matrix[i][j - 1] == ' ' || maze->matrix[i][j - 1] == '1') && direction != LEFT)
        {
            (*stack_size)++;
            maze->matrix[i][j] = '?';

            start_time = tick();

            if (push(array, list, i, j - 1, LEFT))
            {
                return MEMORY_ERROR;
            }

            total_time += tick() - start_time;
        }
    }

    return OK;
}
/**
 * @brief Checks the space in the maze and updates the matrix accordingly.
 *
 * Checks the space in the maze and updates the matrix by marking the space as 'T'.
 *
 * @param maze Pointer to the maze structure.
 * @param i    Current row position in the maze.
 * @param j    Current column position in the maze.
 */
static void check_space(maze_t *maze, const int i, const int j)
{
    if (maze->matrix[i][j] == ' ' && !isdigit(maze->matrix[i][j]))
    {
        maze->matrix[i][j] = 'T';
    }
}
/**
 * @brief Finds the initial direction of movement in the maze.
 *
 * Finds the initial direction of movement in the maze based on available paths in the vicinity.
 *
 * @param maze Pointer to the maze structure.
 * @param i    Current row position in the maze.
 * @param j    Current column position in the maze.
 * @return An integer representing the initial direction (TOP, RIGHT, BOTTOM, LEFT, or NO_WAY).
 */
static int find_start_direction(const maze_t *const maze, const int i, const int j)
{
    if ((i - 1) >= 0 && maze->matrix[i - 1][j] == ' ')
    {
        return TOP;
    }

    if ((j + 1) < maze->x && maze->matrix[i][j + 1] == ' ')
    {
        return RIGHT;
    }

    if ((i + 1) < maze->y && maze->matrix[i + 1][j] == ' ')
    {
        return BOTTOM;
    }

    if ((j - 1) >= 0 && maze->matrix[i][j - 1] == ' ')
    {
        return LEFT;
    }

    return NO_WAY;
}

/**
 * @brief Moves in a specific direction in the maze and checks for deadlock.
 *
 * Moves in a specific direction in the maze and checks for deadlock. Updates the maze matrix and checks if the
 * movement is a deadlock or not.
 *
 * @param maze      Pointer to the maze structure.
 * @param i         Pointer to the current row position in the maze.
 * @param j         Pointer to the current column position in the maze.
 * @param direction Current direction of movement.
 * @return An integer code indicating whether the movement leads to a deadlock (DEADLOCK) or not (NOT_DEADLOCK).
 */
static int direction_move(maze_t *maze, int *i, int *j, const int direction)
{
    check_space(maze, *i, *j);

    switch (direction)
    {
        case TOP:
            if (--(*i) < 0)
            {
                return DEADLOCK;
            }

            break;
        case RIGHT:
            if (++(*j) > (maze->x - 1))
            {
                return DEADLOCK;
            }

            break;
        case BOTTOM:
            if (++(*i) > (maze->y - 1))
            {
                return DEADLOCK;
            }

            break;
        case LEFT:
            if (--(*j) < 0)
            {
                return DEADLOCK;
            }
    }

    if (maze->matrix[*i][*j] != ' ' && maze->matrix[*i][*j] != '1')
    {
        return DEADLOCK;
    }

    check_space(maze, *i, *j);

    return NOT_DEADLOCK;
}
/**
 * @brief Finds a way through the maze using a stack-based algorithm.
 *
 * Finds a way through the maze using a stack-based algorithm. The type of stack (array or list) is determined
 * by the stack_type parameter. The algorithm writes the steps to the log file specified by LOG_FILE.
 *
 * @param stack_type   Type of stack to be used (STACK_ARRAY or STACK_LIST).
 * @param array        Pointer to the array-based stack.
 * @param list         Pointer to the list-based stack.
 * @param maze         Pointer to the maze structure.
 * @param stack_size   Pointer to the variable storing the stack size.
 * @param max_stack    Maximum size of the stack.
 * @return An integer code indicating the operation result.
 */
int find_way(int stack_type, stack_array_t *array, stack_list_t *list, maze_t *maze,
    int *stack_size, const int max_stack)
{
    __stack_type = stack_type;
    total_time = 0;

    list_element_t **address_array = malloc(max_stack * sizeof(list_element_t *));
    int size = 0;
    int64_t start_time;

    FILE *f = NULL;

    if ((f = fopen(LOG_FILE, "w+")) == NULL)
    {
        return INVALID_FILE;
    }

    int i = maze->i_enter;
    int j = maze->j_enter;
    int direction = find_start_direction(maze, i, j);

    if (direction == NO_WAY)
    {
        print_maze(*maze);
        fprintf(stderr, "There's no way out of this point.\n");
        return NO_WAY;
    }

    do
    {
        do
        {
            if (maze->matrix[i][j] == '1')
            {
                fclose(f);
                free(address_array);
                maze->matrix[maze->i_enter][maze->j_enter] = '0';
                return OK;
            }

            if (checking_for_corners(maze, i, j, array, list, stack_size, direction))
            {
                fclose(f);
                free(address_array);
                return MEMORY_ERROR;
            }

        } while (!direction_move(maze, &i, &j, direction));

        start_time = tick();

        if (peek(array, list, &i, &j, &direction))
        {
            print_maze(*maze);
            fprintf(stderr, "You can't find a way\n");
            return STACK_EMPTY;
        }

        total_time += tick() - start_time;

        print_stack(*list, *array, f, address_array, size);
        address_array[size++] = list->ptr;

        start_time = tick();

        if (pop(array, list))
        {
            print_maze(*maze);
            fprintf(stderr, "You can't find a way.\n");
            return STACK_EMPTY;
        }

        total_time += tick() - start_time;

    } while (true);
}
