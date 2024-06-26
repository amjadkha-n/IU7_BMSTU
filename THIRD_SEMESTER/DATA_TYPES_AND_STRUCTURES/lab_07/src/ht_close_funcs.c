#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/ht_close_funcs.h"

#define FILE_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define MEMORY_ERROR 2

/**
 * @brief Initializes a closed hash table with flags.
 * 
 * @param ht The hash table to be initialized.
 * @param n The size of the hash table.
 */
void init_close_ht(hash_t *ht, int n)
{
	for (int i = 0; i < n; i++)
		ht[i].flag = 0;
}
/**
 * @brief Computes the first hash function for a given key and table size.
 * 
 * @param key The key for which the hash is computed.
 * @param p The size of the hash table.
 * @return The computed hash value.
 */
int hash_func_1(char *key, int p)
{
	size_t sum = 0;
	for (size_t i = 0; i < strlen(key); i++)
		sum += key[i];

	int ret = sum % p;
	return ret;
}
/**
 * @brief Computes the second hash function for a given key and table size.
 * 
 * @param key The key for which the hash is computed.
 * @param p The size of the hash table.
 * @return The computed hash value.
 */
int hash_func_2(char *key, int p)
{
	size_t sum = 0;
	size_t coeff = 1117;
	for (size_t i = 0; i < strlen(key); i++)
	{
		sum += key[i];
		sum *= coeff;
	}
	return sum % p;
}
/**
 * @brief Checks if a given number is prime.
 * 
 * @param x The number to be checked for primality.
 * @return 1 if the number is prime, 0 otherwise.
 */
int is_prime(int x)
{
	if (x < 2)
		return 0;
	for (int k = 2; k <= x / 2; k++)
		if (x % k == 0)
			return 0;
	return 1;
}
/**
 * @brief Rehashes a closed hash table to a larger size.
 * 
 * @param ht The original hash table.
 * @param n The size of the original hash table.
 * @param hashf The hash function to be used.
 * @return EXIT_SUCCESS if successful, MEMORY_ERROR if memory allocation fails.
 */
int rehash_close_ht(hash_t *ht, int *n, int (*hashf) (char *, int ))
{
	hash_t *ht_old = malloc((*n) * sizeof(hash_t));
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
	
	char word_tmp[MAX_LENGHT + 2];

	init_close_ht(ht, *n);
	for (int i = 0; i < nn; i++)
	{
		if (ht_old[i].flag == 1)
		{
			strcpy(word_tmp, ht_old[i].value);
			int hashval = hashf(word_tmp, *n);
			int kcmp = 0;					// количество сравнений
			int j = hashval;				// текущий индекс
			while (kcmp < MAX_SEARCH)
			{
				if (ht[j].flag != 1)	// пустая или удалённая ячейка
				{
					strcpy(ht[j].value, word_tmp);
					ht[j].flag = 1;
					break;
				}
				else if (! strcmp(ht[j].value, word_tmp))	// значение уже добавлено
					break;
				else
				{
					j++;
					if (j == *n) // граница выделенной области памяти
						j = 0;
					kcmp++;
				}
				if (kcmp == MAX_SEARCH)
				{
					int sc = rehash_close_ht(ht, n, hashf);
					if (sc != EXIT_SUCCESS)
					{
						free(ht_old);
						return sc;
					}
					kcmp = 0;
					hashval = hashf(word_tmp, *n);
					j = hashval;
				}
			}
		}
	}
	free(ht_old);
	return EXIT_SUCCESS;
}
/**
 * @brief Reads words from a file and inserts them into a closed hash table.
 * 
 * @param f The file to read from.
 * @param ht The hash table to insert words into.
 * @param n The size of the hash table.
 * @param hashf The hash function to be used.
 * @return EXIT_SUCCESS if successful, EXIT_FAILURE if there is an error reading from the file, MEMORY_ERROR if memory allocation fails.
 */
int hread_close_ht(FILE *f, hash_t *ht, int *n, int (*hashf) (char *, int ))
{
	if (*n <= 0)
		return EXIT_FAILURE;
	
	char word_tmp[MAX_LENGHT + 2];

	if (fscanf(f, "%s", word_tmp) == EOF)
		return EXIT_FAILURE;
	rewind(f);
	
	int sc = 1;
	while (sc == 1)
	{
		sc = fscanf(f, "%s", word_tmp);
		if (sc == EOF)
			return EXIT_SUCCESS;
		if (sc != 1)
			return EXIT_FAILURE;
		int hashval = hashf(word_tmp, *n);
		int kcmp = 0;					// количество сравнений
		int i = hashval;				// текущий индекс
		while (kcmp < MAX_SEARCH)
		{
			if (ht[i].flag != 1)	// пустая или удалённая ячейка
			{
				strcpy(ht[i].value, word_tmp);
				ht[i].flag = 1;
				break;
			}
			else if (! strcmp(ht[i].value, word_tmp))	// значение уже добавлено
				break;
			else
			{
				i++;
				if (i == *n) // граница выделенной области памяти
					i = 0;
				kcmp++;
			}
			if (kcmp == MAX_SEARCH)
			{
				int rc = rehash_close_ht(ht, n, hashf);
				if (rc != EXIT_SUCCESS)
					return rc;
				kcmp = 0;
				hashval = hashf(word_tmp, *n);
				i = hashval;
			}
		}
	}
	return EXIT_SUCCESS;
}
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
int hsearch_close_ht(char *key, hash_t *ht, int n, int *kcmp, int (*hashf) (char *, int ))
{
	int hashval = hashf(key, n);		// вычисление значения хэш-функции
	*kcmp = 0;							// количество сравнений
	int i = hashval;					// текущий индекс
	do
	{
		(*kcmp)++;
		if (ht[i].flag != 1)	// пустая ячейка
			return -1;
		if (! strcmp(ht[i].value, key)) // если значение совпадает
			return i;
		i++;
		if (i == n)	// граница выделенной области памяти
			i = 0;
	}
	while (*kcmp < MAX_SEARCH && i != hashval);
	return -1;
}
/**
 * @brief Removes a word from a closed hash table.
 * 
 * @param key The word to remove.
 * @param ht The hash table to remove from.
 * @param n The size of the hash table.
 * @param hashf The hash function to be used.
 * @return The index of the removed word if successful, -1 otherwise.
 */
int hremove_close_ht(char *key, hash_t *ht, int n, int (*hashf) (char *, int ))
{
	int kcmp = 0;
	int ind = hsearch_close_ht(key, ht, n, &kcmp, hashf);	//индекс элемента
	if (ind != -1)	//элемент существует
	{
		ht[ind].flag = -1;
		return ind;
	}
	return -1;
}
/**
 * @brief Prints the contents of a closed hash table.
 * 
 * @param ht The hash table to print.
 * @param n The size of the hash table.
 */
void hprint_close_ht(hash_t *ht, int n)
{
	printf("Close hash table:\n");
	for (int i = 0; i < n; i++)
	{
		if (ht[i].flag == 1)
		{
			printf("%4d  ->  ", i);
			printf("%s\n", ht[i].value);
		}
		else
			printf("%4d  ->  --\n", i);
	}
}