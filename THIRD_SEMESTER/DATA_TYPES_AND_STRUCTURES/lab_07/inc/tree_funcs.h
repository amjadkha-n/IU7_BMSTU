#ifndef __TREE_FUNCS_H__
#define __TREE_FUNCS_H__

#define MAX_LENGHT 10

typedef struct tree_node node_t;

struct tree_node
{
    char *name;
    node_t *left;
    node_t *right;
};
/**
 * @brief Creates a new node with the specified name.
 * 
 * @param name The name for the new node.
 * @return A pointer to the newly created node.
 */
node_t* node_create(char *name);
/**
 * @brief Inserts a node into a binary tree.
 * 
 * @param tree The root of the binary tree.
 * @param node The node to be inserted.
 * @return The updated root of the binary tree.
 */
node_t* node_insert(node_t *tree, node_t *node);
/**
 * @brief Searches for a node with the specified name in the binary tree.
 * 
 * @param tree The root of the binary tree.
 * @param name The name to search for.
 * @param q_cmp Pointer to store the number of comparisons made during the search.
 * @return A pointer to the found node, or NULL if not found.
 */
node_t* node_search(node_t *tree, const char *name, int *q_cmp);
/**
 * @brief Prints the names of nodes in the binary tree in ascending order.
 * 
 * @param tree The root of the binary tree.
 */
void node_print(node_t *tree);
/**
 * @brief Frees the memory allocated for the binary tree.
 * 
 * @param tree The root of the binary tree.
 */
void tree_free(node_t *tree);
/**
 * @brief Reads words from a file and constructs a binary tree.
 * 
 * @param fsrc The file containing words.
 * @return The root of the constructed binary tree.
 */
node_t* tree_file_read(FILE *fsrc);
/**
 * @brief Finds words in the binary tree that start with a given character.
 * 
 * @param tree The root of the binary tree.
 * @param c The character to search for.
 * @param n Pointer to store the number of found words.
 * @param mode If non-zero, prints the found words.
 * @param q_cmp Pointer to store the number of comparisons made during the search.
 */
void tree_words_char_find(node_t *tree, char c, int *n, int mode, int *q_cmp);
/**
 * @brief Generates a DOT file representing the binary tree.
 * 
 * @param tree The root of the binary tree.
 * @param f The file to write the DOT representation.
 */
node_t* node_delete(node_t *tree, const char *name);
/**
 * @brief Exports the binary tree to a DOT file for visualization.
 * 
 * @param f The file to write the DOT representation.
 * @param tree The root of the binary tree.
 * @param c The character to filter words (0 for no filtering).
 */
void tree_export_to_dot(FILE *f, node_t *tree, char c);


#endif // __TREE_FUNCS_H__