#include <stdio.h>
#include <stdlib.h>

#include "../inc/tree.h"
#include "../inc/stack.h"
#include "../inc/defines.h"
/**
 * @brief Initialize a tree node.
 *
 * This function initializes a tree node with the provided depth,
 * parent, left child, right child, value, and option.
 *
 * @param node Pointer to the node to be initialized.
 * @param depth Depth of the node in the tree.
 * @param parent Pointer to the parent node.
 * @param left Pointer to the left child node.
 * @param right Pointer to the right child node.
 * @param value Value associated with the node.
 * @param option Operator associated with the node.
 */
void node_init(node_t *node, int depth, node_t *parent, node_t *left, node_t *right, int value, char option)
{
    node->depth = depth;
    node->parent = parent;
    node->left = left;
    node->right = right;
    node->value = value;
    node->option = option;
}

/**
 * @brief Create a new tree node.
 *
 * This function creates a new tree node with the provided depth,
 * parent, left child, right child, value, and option. Memory allocation
 * for the new node is handled internally.
 *
 * @param depth Depth of the node in the tree.
 * @param parent Pointer to the parent node.
 * @param left Pointer to the left child node.
 * @param right Pointer to the right child node.
 * @param value Value associated with the node.
 * @param option Operator associated with the node.
 * @return Pointer to the newly created node.
 */
node_t *create_node(int depth, node_t *parent, node_t *left, node_t *right, int value, char option)
{
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL)
        printf("Memory allocation error for a tree node!\n");

    node_init(new_node, depth, parent, left, right, value, option);

    return new_node;
}
/**
 * @brief Create a binary tree from an array of integers.
 *
 * This function creates a binary tree from the given array of integers.
 * The structure of the tree corresponds to a specific arithmetic expression.
 *
 * @param arr Array of integers representing the arithmetic expression.
 * @return Pointer to the root of the created binary tree.
 */
node_t *create_tree(int arr[NUMS_COUNT])
{
    node_t *plus1 = create_node(0, NULL, NULL, NULL, 0, '+');
    node_t *a = create_node(1, plus1, NULL, NULL, arr[0], ' ');
    node_t *multi1 = create_node(1, plus1, NULL, NULL, 0, '*');
    plus1->left = a;
    plus1->right = multi1;


    node_t *b = create_node(2, multi1, NULL, NULL, arr[1], ' ');
    node_t *plus2 = create_node(2, multi1, NULL, NULL, 0, '+');
    multi1->left = b;
    multi1->right = plus2;


    node_t *minus1 = create_node(3, plus2, NULL, NULL, 0, '-');
    node_t *multi2 = create_node(3, plus2, NULL, NULL, 0, '*');
    plus2->left = minus1;
    plus2->right = multi2;


    node_t *plus3 = create_node(4, minus1, NULL, NULL, 0, '+');
    node_t *minus2 = create_node(4, minus1, NULL, NULL, 0, '-');
    minus1->left = plus3;
    minus1->right = minus2;


    node_t *d = create_node(4, multi2, NULL, NULL, arr[3], ' ');
    node_t *plus4 = create_node(4, multi2, NULL, NULL, 0, '+');
    multi2->left = d;
    multi2->right = plus4;

    node_t *c = create_node(5, plus3, NULL, NULL, arr[2], ' ');
    node_t *i = create_node(5, plus3, NULL, NULL, arr[8], ' ');
    plus3->left = c;
    plus3->right = i;

    node_t *e = create_node(5, plus4, NULL, NULL, arr[4], ' ');
    node_t *f = create_node(5, plus4, NULL, NULL, arr[5], ' ');
    plus4->left = e;
    plus4->right = f;

    node_t *g = create_node(5, minus2, NULL, NULL, arr[6], ' ');
    node_t *h = create_node(5, minus2, NULL, NULL, arr[7], ' ');
    minus2->left = g;
    minus2->right = h;

    return plus1;
}
/**
 * @brief Print the binary tree.
 *
 * This function prints the binary tree in a readable format, including
 * the depth, value, and option of each node.
 *
 * @param root Pointer to the root of the binary tree.
 * @param place Internal parameter for proper indentation during printing.
 */
void print_tree(node_t *root, int place)
{
    int add_space = 6;

    place += add_space;

    if (root == NULL)
        return;


    if (root->right != NULL)
        print_tree(root->right, place);

    for (int i = add_space; i < place; i++)
        printf(" ");

    if (root->option != ' ')
        printf("{ %c }\n", root->option);
    else
        printf("{ %d }\n", root->value);

    if (root->left != NULL)
        print_tree(root->left, place);
}
/**
 * @brief Perform a prefix traversal of the binary tree.
 *
 * This function performs a prefix traversal of the binary tree,
 * printing the value or option of each node.
 *
 * @param root Pointer to the root of the binary tree.
 */
void prefix_bypass(node_t *root)
{
    if (root != NULL)
    {
        if (root->option != ' ')
            printf("%c ", root->option);
        else
            printf("%d ", root->value);

        prefix_bypass(root->left);
        prefix_bypass(root->right);
    }
}
/**
 * @brief Perform a postfix traversal of the binary tree.
 *
 * This function performs a postfix traversal of the binary tree,
 * updating the value of each node based on the arithmetic expression.
 * Optionally, it prints the resulting values or options.
 *
 * @param root Pointer to the root of the binary tree.
 * @param mode Flag indicating whether to print the resulting values or not.
 */
void postfix_bypass(node_t *root, int mode)
{
    if (root != NULL)
    {
        postfix_bypass(root->left, mode);
        postfix_bypass(root->right, mode);

        if (root->option == '+')
            root->value = root->left->value + root->right->value;

        else if (root->option == '-')
            root->value = root->left->value - root->right->value;
        else if (root->option == '*')
            root->value = root->left->value * root->right->value;
        else if (mode)
            printf("%d ", root->value);

        if (root->option != ' ' && mode)
            printf("%c ", root->option);
    }
}

/**
 * @brief Perform an infix traversal of the binary tree.
 *
 * This function performs an infix traversal of the binary tree,
 * printing the value or option of each node.
 *
 * @param root Pointer to the root of the binary tree.
 */
void infix_bypass(node_t *root)
{
    if (root != NULL)
    {
        infix_bypass(root->left);

        if (root->option != ' ')
            printf("%c ", root->option);
        else
            printf("%d ", root->value);

        infix_bypass(root->right);
    }
}
