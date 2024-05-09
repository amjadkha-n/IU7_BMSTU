#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/tree_funcs.h"
#include "../inc/avl_funcs.h"
/**
 * @brief Rotates the given node to the left.
 * 
 * @param node The node to be rotated.
 * @return The new root after rotation.
 */
node_t *rotate_left(node_t *node)
{
    node_t *tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    return tmp;
}

/**
 * @brief Rotates the given node to the right.
 * 
 * @param node The node to be rotated.
 * @return The new root after rotation.
 */
node_t *rotate_right(node_t *node)
{
    node_t *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    return tmp;
}

/**
 * @brief Calculates the height of the tree rooted at the given node.
 * 
 * @param root The root of the tree.
 * @return The height of the tree.
 */
int height(node_t *root)
{
    if (!root)
        return 0;
    int hleft = 0, hright = 0;
    if (root && root->left)
        hleft = height(root->left);
    if (root && root->right)
        hright = height(root->right);
    return (hleft < hright) ? hright + 1 : hleft + 1;
}

/**
 * @brief Balances the given AVL tree node.
 * 
 * @param tree The root of the AVL tree.
 * @return The new root after balancing.
 */
node_t *balance(node_t *tree)
{
    if (!tree)
        return NULL;
    int bfactor = height(tree->right) - height(tree->left);
    if (bfactor < -1)
    {
        bfactor = height(tree->left->right) - height(tree->left->left);
        if (bfactor > 0)
            tree->left = rotate_left(tree->left);
        return rotate_right(tree);
    }
    else if (bfactor > 1)
    {
        bfactor = height(tree->right->right) - height(tree->right->left);
        if (bfactor < 0)
            tree->right = rotate_right(tree->right);
        return rotate_left(tree);
    }
    return tree;
}

/**
 * @brief Balances the entire AVL tree.
 * 
 * @param tree The root of the AVL tree.
 * @return The new root after balancing.
 */
node_t *tree_balance(node_t *tree)
{
    if (!tree)
        return NULL;

    if (tree->left)
        tree->left = tree_balance(tree->left);

    if (tree->right)
        tree->right = tree_balance(tree->right);

    while (abs(height(tree->right) - height(tree->left)) > 1)
        tree = balance(tree);

    if (tree->left)
        tree->left = tree_balance(tree->left);

    if (tree->right)
        tree->right = tree_balance(tree->right);

    return tree;
}

/**
 * @brief Removes a node with the given data from the AVL tree.
 * 
 * @param tree The root of the AVL tree.
 * @param data The data to be removed.
 * @return The new root after removal and balancing.
 */
node_t *avl_remove(node_t *tree, char *data)
{
    if (!tree)
        return NULL;

    if (strcmp(data, tree->name) < 0)
        tree->left = avl_remove(tree->left, data);
    else if (strcmp(data, tree->name) > 0)
        tree->right = avl_remove(tree->right, data);
    else
    {
        node_t *tmpl = tree->left;
        node_t *tmpr = tree->right;
        free(tree);

        if (!tmpl)
            return tmpr;

        node_t *tmax = tmpl;
        while (tmax->right)
            tmax = tmax->right;
        if (tmax == tmpl)
        {
            tmax->right = tmpr;
            return balance(tmax);
        }

        node_t *tmp = tmpl;
        while (tmp->right)
            tmp = tmp->right;
        tmpl->right = tmp->left;

        tmax->left = balance(tmpl);
        tmax->right = tmpr;
        return balance(tmax);
    }
    return balance(tree);
}
