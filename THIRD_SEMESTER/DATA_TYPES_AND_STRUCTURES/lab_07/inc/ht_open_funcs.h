#ifndef __HT_OPEN_FUNCS__H__

#define __HT_OPEN_FUNCS__H__

typedef struct hash_node hash_node_t;

struct hash_node
{
	char data[MAX_LENGHT + 2];
	hash_node_t *next;
};


typedef struct open_hash
{
	hash_node_t *value;
	char flag;
} open_hash_t;
/**
 * @brief Frees the memory allocated for an open hash table.
 * 
 * @param ht The open hash table to be freed.
 * @param n The size of the hash table.
 */
void free_open_ht(open_hash_t *ht, int n);
/**
 * @brief Creates a new hash node with the given data.
 * 
 * @param str The data for the new hash node.
 * @return A pointer to the newly created hash node.
 */
hash_node_t *create_hash_node(char *str);
/**
 * @brief Rehashes an open hash table to a larger size.
 * 
 * @param ht The original open hash table.
 * @param n The size of the original hash table.
 * @param hashf The hash function to be used.
 * @return EXIT_SUCCESS if successful, MEMORY_ERROR if memory allocation fails.
 */
int rehash_open_ht(open_hash_t *ht, int *n, int (*hashf) (char *, int ));
/**
 * @brief Reads words from a file and inserts them into an open hash table.
 * 
 * @param f The file to read from.
 * @param ht The open hash table to insert words into.
 * @param n The size of the hash table.
 * @param hashf The hash function to be used.
 * @return EXIT_SUCCESS if successful, EXIT_FAILURE if there is an error reading from the file, MEMORY_ERROR if memory allocation fails.
 */
int hread_open_ht(FILE *f, open_hash_t *ht, int *n, int (*hashf) (char *, int ));
/**
 * @brief Searches for a word in an open hash table.
 * 
 * @param key The word to search for.
 * @param ht The open hash table to search in.
 * @param n The size of the hash table.
 * @param kcmp The number of comparisons made during the search.
 * @param hashf The hash function to be used.
 * @return The index of the word if found, -1 otherwise.
 */
int hsearch_open_ht(char *key, open_hash_t *ht, int n, int *kcmp, int (*hashf) (char *, int ));
/**
 * @brief Removes a word from an open hash table.
 * 
 * @param key The word to remove.
 * @param ht The open hash table to remove from.
 * @param n The size of the hash table.
 * @param hashf The hash function to be used.
 * @return The index of the removed word if successful, -1 otherwise.
 */
int hremove_open_ht(char *key, open_hash_t *ht, int n, int (*hashf) (char *, int ));
/**
 * @brief Prints the contents of an open hash table.
 * 
 * @param ht The open hash table to print.
 * @param n The size of the hash table.
 */
void hprint_open_ht(open_hash_t *ht, int n);


#endif // __HT_OPEN_FUNCS__H__