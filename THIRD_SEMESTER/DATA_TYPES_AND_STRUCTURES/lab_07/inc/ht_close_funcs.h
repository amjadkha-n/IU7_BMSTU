#ifndef __HT_CLOSE_FUNCS__H__

#define __HT_CLOSE_FUNCS__H__

#define MAX_LENGHT 10
#define MAX_SIZE 10000
#define MAX_SEARCH 4

typedef struct hash
{
	char value[MAX_LENGHT + 2];
	char flag;
} hash_t;
/**
 * @brief Initializes a closed hash table with flags.
 * 
 * @param ht The hash table to be initialized.
 * @param n The size of the hash table.
 */
void init_close_ht(hash_t *ht, int n);
/**
 * @brief Computes the first hash function for a given key and table size.
 * 
 * @param key The key for which the hash is computed.
 * @param p The size of the hash table.
 * @return The computed hash value.
 */
int hash_func_1(char *key, int p);
/**
 * @brief Computes the second hash function for a given key and table size.
 * 
 * @param key The key for which the hash is computed.
 * @param p The size of the hash table.
 * @return The computed hash value.
 */
int hash_func_2(char *key, int p);
/**
 * @brief Checks if a given number is prime.
 * 
 * @param x The number to be checked for primality.
 * @return 1 if the number is prime, 0 otherwise.
 */
int is_prime(int x);
/**
 * @brief Rehashes a closed hash table to a larger size.
 * 
 * @param ht The original hash table.
 * @param n The size of the original hash table.
 * @param hashf The hash function to be used.
 * @return EXIT_SUCCESS if successful, MEMORY_ERROR if memory allocation fails.
 */
int rehash_close_ht(hash_t *ht, int *n, int (*hashf) (char *, int ));
/**
 * @brief Reads words from a file and inserts them into a closed hash table.
 * 
 * @param f The file to read from.
 * @param ht The hash table to insert words into.
 * @param n The size of the hash table.
 * @param hashf The hash function to be used.
 * @return EXIT_SUCCESS if successful, EXIT_FAILURE if there is an error reading from the file, MEMORY_ERROR if memory allocation fails.
 */
int hread_close_ht(FILE *f, hash_t *ht, int *n, int (*hashf) (char *, int ));
/**
 * @brief Searches for a word in a closed hash table.
 * 
 * @param key The word to search for.
 * @param ht The hash table to search in.
 * @param n The size of the hash table.
 * @param kcmp The number of comparisons made during the search.
 * @param hashf The hash function to be used.
 * @return The index of the word if found, -1 otherwise.
 */
int hsearch_close_ht(char *key, hash_t *ht, int n, int *kcmp, int (*hashf) (char *, int ));
/**
 * @brief Removes a word from a closed hash table.
 * 
 * @param key The word to remove.
 * @param ht The hash table to remove from.
 * @param n The size of the hash table.
 * @param hashf The hash function to be used.
 * @return The index of the removed word if successful, -1 otherwise.
 */
int hremove_close_ht(char *key, hash_t *ht, int n, int (*hashf) (char *, int ));
/**
 * @brief Prints the contents of a closed hash table.
 * 
 * @param ht The hash table to print.
 * @param n The size of the hash table.
 */
void hprint_close_ht(hash_t *ht, int n);

#endif // __HT_CLOSE_FUNCS__H__
