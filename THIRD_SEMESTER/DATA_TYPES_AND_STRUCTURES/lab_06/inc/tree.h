#ifndef __TREE__H__
#define __TREE__H__

#include "defines.h"
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

typedef struct node node_t;

struct node {
    int depth;      // vertex depth
    node_t *left;   // left "child"
    node_t *right;  // right "child"
    node_t *parent; // parent node
    int value;      // values in node
    char option;    // operation of node
};

/**
 * @brief Print the binary tree.
 *
 * This function prints the binary tree in a readable format, including
 * the depth, value, and option of each node.
 *
 * @param root Pointer to the root of the binary tree.
 * @param place Internal parameter for proper indentation during printing.
 */
void print_tree(node_t *root, int place);
/**
 * @brief Create a binary tree from an array of integers.
 *
 * This function creates a binary tree from the given array of integers.
 * The structure of the tree corresponds to a specific arithmetic expression.
 *
 * @param arr Array of integers representing the arithmetic expression.
 * @return Pointer to the root of the created binary tree.
 */
node_t *create_tree(int arr[NUMS_COUNT]);

/**
 * @brief Perform a prefix traversal of the binary tree.
 *
 * This function performs a prefix traversal of the binary tree,
 * printing the value or option of each node.
 *
 * @param root Pointer to the root of the binary tree.
 */
void prefix_bypass(node_t *root);
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
void postfix_bypass(node_t *root, int mode);

/**
 * @brief Perform an infix traversal of the binary tree.
 *
 * This function performs an infix traversal of the binary tree,
 * printing the value or option of each node.
 *
 * @param root Pointer to the root of the binary tree.
 */
void infix_bypass(node_t *root);
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
node_t *create_node(int depth, node_t *parent, node_t *left, node_t *right, int value, char option);

#endif
