#include "associative_array.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct element_t element_t;

struct element_t
{
    char *key;
    int value;
    element_t *next;
};

struct assoc_array_type
{
    element_t *head;
};
assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = calloc(1, sizeof(struct assoc_array_type));
    if (!arr)
        return NULL;
    arr->head = NULL;
    return arr;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if ((!arr) || (!(*arr)))
        return;

    element_t *tmp = (*arr)->head;

    while (tmp)
    {
        element_t *next = tmp->next;
        free(tmp->key);
        free(tmp);
        tmp = next;
    }

    free(*arr);
    (*arr) = NULL;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    element_t *tmp = arr->head;

    while (tmp)
    {
        element_t *next = tmp->next;
        free(tmp->key);
        free(tmp);
        tmp = next;
    }

    arr->head = NULL;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if ((!arr) || (!key) || (strlen(key) == 0) || (!num))
        return ASSOC_ARRAY_INVALID_PARAM;

    element_t *tmp = arr->head;
    while (tmp)
    {
        if (strcmp(key, tmp->key) == 0)
        {
            *num = &(tmp->value);
            return ASSOC_ARRAY_OK;
        }
        tmp = tmp->next;
    }
    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if ((!arr) || (!num))
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!(arr->head))
        return ASSOC_ARRAY_NOT_FOUND;

    element_t *tmp = arr->head;
    char *min = tmp->key;
    *num = &(tmp->value);
    tmp = tmp->next;

    while (tmp)
    {
        if (strcmp(tmp->key, min) < 0)
        {
            min = tmp->key;
            *num = &(tmp->value);
        }
        tmp = tmp->next;
    }
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if ((!arr) || (!num))
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!(arr->head))
        return ASSOC_ARRAY_NOT_FOUND;

    element_t *tmp = arr->head;

    char *max = tmp->key;
    *num = &(tmp->value);
    tmp = tmp->next;

    while (tmp)
    {
        if (strcmp(tmp->key, max) > 0)
        {
            max = tmp->key;
            *num = &(tmp->value);
        }
        tmp = tmp->next;
    }
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if ((!arr) || (!action))
        return ASSOC_ARRAY_INVALID_PARAM;

    element_t *tmp = arr->head;

    while (tmp)
    {
        action(tmp->key, &(tmp->value), param);
        tmp = tmp->next;
    }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if ((!arr) || (!key) || (strlen(key) == 0))
        return ASSOC_ARRAY_INVALID_PARAM;

    element_t *tmp = arr->head;

    while (tmp)
    {
        if (strcmp(key, tmp->key) == 0)
            return ASSOC_ARRAY_KEY_EXISTS;
        tmp = tmp->next;
    }

    element_t *new = calloc(1, sizeof(element_t));
    if (!new)
        return ASSOC_ARRAY_MEM;

    new->value = num;
    new->key = calloc(1, sizeof(char) * (strlen(key) + 1));
    if (!(new->key))
    {
        free(new);
        return ASSOC_ARRAY_MEM;
    }

    strcpy(new->key, key);
    new->next = arr->head;
    arr->head = new;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if ((!arr) || (!key) || (strlen(key) == 0))
        return ASSOC_ARRAY_INVALID_PARAM;

    element_t *cur, *prev = NULL;

    for (cur = arr->head; cur; cur = cur->next)
    {
        if (strcmp(cur->key, key) == 0)
        {
            if (prev)
                prev->next = cur->next;
            else
                arr->head = cur->next;

            free(cur->key);
            free(cur);
            return ASSOC_ARRAY_OK;
        }
        prev = cur;
    }
    return ASSOC_ARRAY_NOT_FOUND;
}

