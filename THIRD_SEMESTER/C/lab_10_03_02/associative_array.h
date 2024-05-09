#ifndef ASSOC_ARR_H__

#define ASSOC_ARR_H__


typedef struct assoc_array_type *assoc_array_t;


typedef enum error_t
{
    ASSOC_ARRAY_OK = 0,
    ASSOC_ARRAY_INVALID_PARAM, 
    ASSOC_ARRAY_MEM,
    ASSOC_ARRAY_NOT_FOUND,
    ASSOC_ARRAY_KEY_EXISTS,
} assoc_array_error_t;

assoc_array_t assoc_array_create(void);
void assoc_array_destroy(assoc_array_t *arr);
assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num);
assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num);
assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key);
assoc_array_error_t assoc_array_clear(assoc_array_t arr);
assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param);
assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num);
assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num);


#endif

