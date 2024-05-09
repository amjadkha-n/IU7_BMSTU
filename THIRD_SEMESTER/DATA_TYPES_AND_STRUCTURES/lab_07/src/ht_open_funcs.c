#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/ht_close_funcs.h"
#include "../inc/ht_open_funcs.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2

/**
 * @brief Frees the memory allocated for an open hash table.
 * 
 * @param ht The open hash table to be freed.
 * @param n The size of the hash table.
 */
void free_open_ht(open_hash_t *ht, int n)
{
	hash_node_t *tmp = NULL;
	hash_node_t *tmp_next = NULL;
	for (int i = 0; i < n; i++)
	{
		ht[i].flag = 0;
		if (ht[i].value)
			tmp_next = ht[i].value;

		while(tmp_next)
		{
			tmp = tmp_next;
			tmp_next = tmp_next->next;
			if (tmp)
				free(tmp);
		}
	}
}
/**
 * @brief Creates a new hash node with the given data.
 * 
 * @param str The data for the new hash node.
 * @return A pointer to the newly created hash node.
 */
hash_node_t *create_hash_node(char *str)
{
	hash_node_t *node = malloc(sizeof(hash_node_t));
	if (!node)
		return NULL;
	strcpy(node->data, str);
	node->next = NULL;
	return node;
}
/**
 * @brief Rehashes an open hash table to a larger size.
 * 
 * @param ht The original open hash table.
 * @param n The size of the original hash table.
 * @param hashf The hash function to be used.
 * @return EXIT_SUCCESS if successful, MEMORY_ERROR if memory allocation fails.
 */
int rehash_open_ht(open_hash_t *ht, int *n, int (*hashf) (char *, int ))
{
	open_hash_t *ht_old = malloc((*n) * sizeof(open_hash_t));
	if (!ht_old)
		return MEMORY_ERROR;

	for (int i = 0; i < *n; i++)
		ht_old[i] = ht[i];

	int nn = *n;
	*n = *n * 2 + 1;
	while (!is_prime(*n))
		*n += 2;

	if (*n > MAX_SIZE)
	{
		free(ht_old);
		return MEMORY_ERROR;
	}

	for (int i = 0; i < (*n); i++)
	{
		ht[i].flag = 0;
		ht[i].value = NULL;
	}
	for (int i = 0; i < nn; i++)
	{
		if (ht_old[i].flag != 0)
		{
			hash_node_t *tmp_node = NULL;
			hash_node_t *cur_node = NULL;
			
			cur_node = ht_old[i].value;
			while (cur_node)       
			{
				int hashval = hashf(cur_node->data, *n);
				int j = hashval;
				if (ht[j].flag == 0)
				{
					tmp_node = create_hash_node(cur_node->data);
					if (!(tmp_node))
						return MEMORY_ERROR;
					ht[j].flag++;
					ht[j].value = tmp_node;
					cur_node = cur_node->next;
				}
				else if (ht[j].flag < MAX_SEARCH)
				{
					tmp_node = ht[j].value;
					while (tmp_node->next)
						tmp_node = tmp_node->next;

					tmp_node->next = create_hash_node(cur_node->data);
					if (!(tmp_node->next))
						return MEMORY_ERROR;
					ht[j].flag++;

					cur_node = cur_node->next;
				}
				else if (ht[j].flag == MAX_SEARCH)
				{
					int sc = rehash_open_ht(ht, n, hashf);
					if (sc != EXIT_SUCCESS)
					{
						free(ht_old);
						return sc;
					}
				}
			}
		}
	}

	return EXIT_SUCCESS;
}
/**
 * @brief Reads words from a file and inserts them into an open hash table.
 * 
 * @param f The file to read from.
 * @param ht The open hash table to insert words into.
 * @param n The size of the hash table.
 * @param hashf The hash function to be used.
 * @return EXIT_SUCCESS if successful, EXIT_FAILURE if there is an error reading from the file, MEMORY_ERROR if memory allocation fails.
 */

int hread_open_ht(FILE *f, open_hash_t *ht, int *n, int (*hashf) (char *, int ))
{
	if (*n <= 0)
		return EXIT_FAILURE;
	
	char word_tmp[MAX_LENGHT + 2];

	if (fscanf(f, "%s", word_tmp) == EOF)
		return EXIT_FAILURE;
	rewind(f);
	
	int sc = 1;
	int new = 1;
	int hashval;
	int i;
	while (sc == 1)
	{
		if (new)
		{
			sc = fscanf(f, "%s", word_tmp);
			if (sc == EOF)
				return EXIT_SUCCESS;
			if (sc != 1)
				return EXIT_FAILURE;

			hashval = hashf(word_tmp, *n);
			i = hashval;
		}
		hash_node_t *tmp_node = NULL;
		hash_node_t *cur_node = NULL;
		if (ht[i].flag == 0)
		{
			new = 1;
			tmp_node = create_hash_node(word_tmp);
			if (!tmp_node)
				return MEMORY_ERROR;
			ht[i].value = tmp_node;
			ht[i].flag++;
		}
		else if (ht[i].flag < MAX_SEARCH)
		{
			new = 1;
			cur_node = ht[i].value;
			if (! strcmp(cur_node->data, word_tmp))
			{

				continue;
			}
			int exist = 0;
			while (cur_node->next)
			{
				cur_node = cur_node->next;
				if (! strcmp(cur_node->data, word_tmp))
				{
					exist = 1;
					break;
				}
			}
			if (!exist)
			{
				tmp_node = create_hash_node(word_tmp);
				if (!tmp_node)
					return MEMORY_ERROR;
				cur_node->next = tmp_node;
				ht[i].flag++;
			}
		}
		else if (ht[i].flag == MAX_SEARCH)
		{
			new = 1;
			cur_node = ht[i].value;
			if (! strcmp(cur_node->data, word_tmp))
			{
				continue;
			}
			int exist = 0;
			while (cur_node->next)                       // значение уже добавлено
			{
				cur_node = cur_node->next;
				if (! strcmp(cur_node->data, word_tmp))
				{
					exist = 1;
					break;
				}
			}
			if (!exist)
			{
				int rc = rehash_open_ht(ht, n, hashf);
				if (rc != EXIT_SUCCESS)
					return rc;
				hashval = hashf(word_tmp, *n);
				i = hashval;
				new = 0;
			}
		}
	}
	return EXIT_SUCCESS;
}
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
int hsearch_open_ht(char *key, open_hash_t *ht, int n, int *kcmp, int (*hashf) (char *, int ))
{
	int hashval = hashf(key, n);		// вычисление значения хэш-функции
	*kcmp = 0;							// количество сравнений
	int i = hashval;					// текущий индекс
	hash_node_t *cur_node = NULL;

	if (ht[i].flag == 0)
		return -1;
	else
	{
		cur_node = ht[i].value;
		while (cur_node)
		{
			(*kcmp)++;
			if (!strcmp(cur_node->data, key))
				return i;
			cur_node = cur_node->next;
		}
	}
	return -1;
}
/**
 * @brief Removes a word from an open hash table.
 * 
 * @param key The word to remove.
 * @param ht The open hash table to remove from.
 * @param n The size of the hash table.
 * @param hashf The hash function to be used.
 * @return The index of the removed word if successful, -1 otherwise.
 */
int hremove_open_ht(char *key, open_hash_t *ht, int n, int (*hashf) (char *, int ))
{
	int kcmp = 0;
	int ind = hsearch_open_ht(key, ht, n, &kcmp, hashf);	//индекс элемента
	if (ind != -1)	//элемент существует
	{
		ht[ind].flag--;
		hash_node_t *cur_node = ht[ind].value;
		hash_node_t *prev_node = ht[ind].value;
		while (cur_node)
		{
			if (!strcmp(cur_node->data, key))
			{
				if (prev_node != cur_node)
					prev_node->next = cur_node->next;
				else
					ht[ind].value = cur_node->next;
				
				free(cur_node);
				break;
			}
			prev_node = cur_node;
			cur_node = cur_node->next;
		}
		return ind;
	}
	return -1;
}
/**
 * @brief Prints the contents of an open hash table.
 * 
 * @param ht The open hash table to print.
 * @param n The size of the hash table.
 */
void hprint_open_ht(open_hash_t *ht, int n)
{
	printf("Open hash table:\n");
	hash_node_t *cur_node = NULL;
	for (int i = 0; i < n; i++)
	{
		if (ht[i].flag > 0)
		{
			printf("%4d  ->  ", i);
			cur_node = ht[i].value;
			while (cur_node)
			{
				printf("%s  ", cur_node->data);
				cur_node = cur_node->next;
			}
			printf("\n");
		}
		else
			printf("%4d  ->  --\n", i);
	}
}