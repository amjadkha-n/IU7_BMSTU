#ifndef __AVL_FUNCS__H__

#define __AVL_FUNCS__H__
/**
 * @brief Balances the entire AVL tree.
 * 
 * @param tree The root of the AVL tree.
 * @return The new root after balancing.
 */
node_t* tree_balance(node_t *tree);
/**
 * @brief Removes a node with the given data from the AVL tree.
 * 
 * @param tree The root of the AVL tree.
 * @param data The data to be removed.
 * @return The new root after removal and balancing.
 */
node_t *avl_remove(node_t *tree, char *data);


#endif //__AVL_FUNCS__H__