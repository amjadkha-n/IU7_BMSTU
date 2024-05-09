#include <stdio.h>
#include <time.h>

#include "../inc/tree.h"
#include "../inc/stack.h"
#include "../inc/defines.h"

/**
 * @brief Main function to demonstrate binary tree operations.
 * 
 * This program creates a binary tree based on user input and performs various
 * tree traversals (prefix, infix, postfix). It also evaluates an expression using
 * both a binary tree and a stack-based approach. Additionally, the program allows
 * users to add and remove vertices from the binary tree.
 * 
 * @return EXIT_SUCCESS if the program executes successfully, SCANF_ERR or WRONG_DELETE
 *         in case of input errors, or other error codes based on the application.
 */
int main(void)
{
    printf("-------------------------------------------------\n");
    printf("           Lab-No.6 Binary tree\n");
    printf("-------------------------------------------------\n\n");

    int arr[NUMS_COUNT];

    printf("Enter %d integer values for A, B, C ... I: ", NUMS_COUNT);
    for (int i = 0; i < NUMS_COUNT; i++)
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Mistake! An integer is required.\n");
            return SCANF_ERR;
        }

    printf("\n\nThe resulting expression:\n");
    printf("%d + (%d * (%d + (%d * (%d + %d) - (%d - %d)) + %d))\n\n",
    arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8]);

    node_t *root = create_tree(arr);

    printf("\n\nThe resulting binary tree:\n");
    print_tree(root, 0);

    printf("Prefix bypass:\n");
    prefix_bypass(root);

    printf("\n\nInfix bypass:\n");
    infix_bypass(root);

    printf("\n\nPostfix bypass:\n");
    postfix_bypass(root, 1);
    printf("\n\n");

    int temp = 0;
    clock_t begin = clock();

    while (temp++ < 1000000)
        postfix_bypass(root, 0);

    clock_t end = clock();

    printf("The result of the expression (by tree): %d\n\n", root->value);
    printf("Time to calculate the expression on the tree: %f\n\n", (double)(end - begin) / 1000000);

    temp = 0;
    int res = 0;
    begin = clock();

    // while (temp++ < 1000000)
    res = stack_res(arr);

    end = clock();

    printf("The result of the expression (on the stack): %d\n\n", res);

    int n, val, rc = 0;
    printf("How many vertices do you want to add to the new empty integer tree?\n");

    if ((rc = scanf("%d", &n) != 1))
    {
        printf("Ошибка! Требуется целое число.\n");
        return SCANF_ERR;
    }

    if (n > 0)
    {
        printf("Enter the value of the root vertex: ");
        if ((scanf("%d", &val) != 1))
        {
            printf("Mistake! An integer is required.\n");
            return SCANF_ERR;
        }

        begin = clock();

        root = create_node(0, NULL, NULL, NULL, val, ' ');

        node_t *old_node = root;
        temp = 1;
        while (temp++ < n)
        {
            printf("Enter the value of the %dth vertex: ", temp);
            if (scanf("%d", &val) != 1)
            {
                printf("Mistake! An integer is required.\n");
                return SCANF_ERR;
            }

            node_t *new_node = create_node(0, old_node, NULL, NULL, val, ' ');
            old_node->left = new_node;
            old_node = new_node;
        }

        printf("\n\nThe resulting tree:\n");
        print_tree(root, 0);
    }


    int m;

    printf("\n\nHow many vertices do you want to leave from the tree of integers?\ninput: ");
    if ((rc = scanf("%d", &m) != 1))
    {
        printf("Mistake! An integer is required.\n");
        return SCANF_ERR;
    }

    if (m > n)
    {
        printf("Mistake! It is impossible to leave more nodes than there are.\n");
        return WRONG_DELETE;
    }

    if (m > 0)
    {
        node_t *old_node = root;
        node_t *new_node = root;
        m--;

        temp = 0;
        while (temp++ < m)
        {
            new_node = old_node->left;
            old_node = new_node;
        }

        new_node->left = NULL;

        print_tree(root, 0);
    }

    return EXIT_SUCCESS;
}
