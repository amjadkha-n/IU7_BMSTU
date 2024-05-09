#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../inc/tree_funcs.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2
/**
 * @brief Creates a new node with the specified name.
 * 
 * @param name The name for the new node.
 * @return A pointer to the newly created node.
 */
node_t* node_create(char *name)
{
    node_t *node = malloc(sizeof(node_t));
    if (node)
    {
        node->name = name;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}
/**
 * @brief Inserts a node into a binary tree.
 * 
 * @param tree The root of the binary tree.
 * @param node The node to be inserted.
 * @return The updated root of the binary tree.
 */
node_t* node_insert(node_t *tree, node_t *node)
{
    if (tree == NULL)
        return node;
    
    int cmp = strcmp(node->name, tree->name);
    if (cmp < 0)
        tree->left = node_insert(tree->left, node);
    if (cmp > 0)
        tree->right = node_insert(tree->right, node);
    
    return tree;
}
/**
 * @brief Searches for a node with the specified name in the binary tree.
 * 
 * @param tree The root of the binary tree.
 * @param name The name to search for.
 * @param q_cmp Pointer to store the number of comparisons made during the search.
 * @return A pointer to the found node, or NULL if not found.
 */
node_t* node_search(node_t *tree, const char *name, int *q_cmp)
{
    int cmp;

    while (tree != NULL)
    {
        (*q_cmp)++;
        cmp = strcmp(name, tree->name);
        if (cmp == 0)
            return tree;
        else if (cmp < 0)
            tree = tree->left;
        else
            tree = tree->right;
    }

    return NULL;
}
/**
 * @brief Prints the names of nodes in the binary tree in ascending order.
 * 
 * @param tree The root of the binary tree.
 */
void node_print(node_t *tree)
{
    if (tree == NULL)
        return;

    node_print(tree->left);
    printf("%s ", tree->name);
    node_print(tree->right);
}
/**
 * @brief Frees the memory allocated for the binary tree.
 * 
 * @param tree The root of the binary tree.
 */
void tree_free(node_t *tree)
{
    if (tree == NULL)
        return;

    tree_free(tree->left);
    tree_free(tree->right);
    free(tree->name);
    free(tree);
}

/**
 * @brief Reads words from a file and constructs a binary tree.
 * 
 * @param fsrc The file containing words.
 * @return The root of the constructed binary tree.
 */
node_t* tree_file_read(FILE *fsrc)
{
    node_t* init_tree = NULL;
    char word_tmp[MAX_LENGHT + 2];
	int tmp = fscanf(fsrc, "%s", word_tmp);
	if (strlen(word_tmp) > MAX_LENGHT)
		return NULL;

    while (tmp == 1)   
    {
        node_t* tmp_node = NULL;
        char *new_word = malloc((strlen(word_tmp) + 1) * sizeof(char));
        if (new_word == NULL)
            return NULL;

        strncpy(new_word, word_tmp, strlen(word_tmp) + 1);
        tmp_node = node_create(new_word);
        if (tmp_node == NULL)
            return NULL;

        init_tree = node_insert(init_tree, tmp_node);

        tmp = fscanf(fsrc, "%s", word_tmp);
        if (strlen(word_tmp) > MAX_LENGHT)
		    return NULL;
    }

    return init_tree;
}
/**
 * @brief Finds words in the binary tree that start with a given character.
 * 
 * @param tree The root of the binary tree.
 * @param c The character to search for.
 * @param n Pointer to store the number of found words.
 * @param mode If non-zero, prints the found words.
 * @param q_cmp Pointer to store the number of comparisons made during the search.
 */
void tree_words_char_find(node_t *tree, char c, int *n, int mode, int *q_cmp)
{
    if (tree == NULL)
        return;
    
    (*q_cmp)++;
    if (tree->name[0] == c)
    {
        (*n)++;
        if (mode)
            printf("%s ", tree->name);
        tree_words_char_find(tree->left, c, n, mode, q_cmp);
        tree_words_char_find(tree->right, c, n, mode, q_cmp);
    }
    else if (tree->name[0] > c)
        tree_words_char_find(tree->left, c, n, mode, q_cmp);
    else
        tree_words_char_find(tree->right, c, n, mode, q_cmp);

}
/**
 * @brief Finds words in the binary tree that contain a given character.
 * 
 * @param tree The root of the binary tree.
 * @param c The character to search for.
 * @param n Pointer to store the number of found words.
 * @param words_arr Array to store found words.
 */
void tree_words_char_find_arr(node_t *tree, char c, int *n, char *words_arr[])
{
    if (tree == NULL)
        return;

    tree_words_char_find_arr(tree->left, c, n, words_arr);
    if (memchr(tree->name, c, sizeof(char)) != NULL)
    {
        (*n)++;
        char *tmp_word = malloc((strlen(tree->name) + 1) * sizeof(char));
        strcpy(tmp_word, tree->name);
        words_arr[*n - 1] = tmp_word;
    }
    tree_words_char_find_arr(tree->right, c, n, words_arr);
}
/**
 * @brief Deletes a node with the specified name from the binary tree.
 * 
 * @param tree The root of the binary tree.
 * @param name The name to be deleted.
 * @return The updated root of the binary tree.
 */
node_t* node_delete(node_t *tree, const char *name)
{
    int cmp, flag = 0;
    node_t *parent = tree;
    node_t *del_node = tree;
    node_t *tmp_node = NULL;

    while (del_node != NULL)
    {
        cmp = strcmp(name, del_node->name);
        if (cmp == 0)
            break;
        else if (cmp < 0)
        {    
            parent = del_node;
            del_node = del_node->left;
        }
        else
        {
            parent = del_node;
            del_node = del_node->right;
        }
    }

    if (del_node == NULL)
        return tree;

    
    if (del_node->left == NULL && del_node->right == NULL)
    {
        if (del_node == tree)
            flag = 1;

        if (parent->left == del_node)
            parent->left = NULL;
        else
            parent->right = NULL;

        free(del_node->name);
        free(del_node);

        if (flag)
            tree = NULL;
    }

    else if (del_node->left == NULL || del_node->right == NULL)
    {
        if (del_node == tree)
            flag = 1;

        if (del_node->left != NULL)
            tmp_node = del_node->left;
        else
            tmp_node = del_node->right;


        if (parent->left == del_node)
            parent->left = tmp_node;
        else
            parent->right = tmp_node;

        free(del_node->name);
        free(del_node);

        if (flag)
            tree = tmp_node;
    }
    
    else
    {
        if (del_node == tree)
            flag = 1;

        node_t *parent_min = del_node;
        node_t *min_elem = del_node->right;
        while (min_elem->left != NULL)
        {
            parent_min = min_elem;
            min_elem = min_elem->left;
        }


        if (parent_min->left == min_elem)
            parent_min->left = min_elem->right;
        else
            parent_min->right = min_elem->right;
        
        min_elem->left = del_node->left;
        min_elem->right = del_node->right;
        
        if (parent->left == del_node)
            parent->left = min_elem;
        else
            parent->right = min_elem;

        free(del_node->name);
        free(del_node);

        if (flag)
            tree = min_elem;
    }

    return tree;
}

/**
 * @brief Generates a DOT file representing the binary tree.
 * 
 * @param tree The root of the binary tree.
 * @param f The file to write the DOT representation.
 */
void node_to_dot(node_t *tree, FILE *f)
{
    if (tree == NULL)
        return;

    if (tree->left)
        fprintf(f, "%s -> %s;\n", tree->name, tree->left->name);

    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->name, tree->right->name);

    node_to_dot(tree->left, f);
    node_to_dot(tree->right, f);
}
/**
 * @brief Exports the binary tree to a DOT file for visualization.
 * 
 * @param f The file to write the DOT representation.
 * @param tree The root of the binary tree.
 * @param c The character to filter words (0 for no filtering).
 */
void tree_export_to_dot(FILE *f, node_t *tree, char c)
{
    fprintf(f, "digraph Words {\n");

    if (c != 0)
    {
        char *words_arr[100];
        int n = 0;
        tree_words_char_find_arr(tree, c, &n, words_arr);
        fprintf(f, "subgraph tier1\n{\nnode [color=\"lightgreen\",style=\"filled\",group=\"tier1\"]\n");
        for (int i = 0; i < n; i++)
        {
            fprintf(f, "%s\n", words_arr[i]);
            free(words_arr[i]);
        }
        n = 0;
        fprintf(f, "}\n");
    }

    node_to_dot(tree, f);

    fprintf(f, "}\n");
}