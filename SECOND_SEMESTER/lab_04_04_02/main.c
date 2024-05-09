#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include "my_string.h"

#define TRUE 1
#define FALSE 0

#define DIGITS "0123456789"

#define MONTH_COUNT 12
#define WORDS_COUNT 3

typedef struct date
{
    char str_day[MAX_STR_SIZE];
    int int_day;
    char str_month[MAX_STR_SIZE];
    size_t index_month;
    char str_year[MAX_STR_SIZE];
    int int_year;
} date_t;

char months[MONTH_COUNT][MAX_STR_SIZE] = { "january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december" };

int days_in_months[MONTH_COUNT] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


int is_init_date(char *str, date_t *date)
{
    char arr_words[MAX_STR_SIZE / 2][MAX_STR_SIZE];
    size_t count_words = 0;

    size_t len_str = strlen(str);

    if (split_str(str, len_str, arr_words, &count_words))
        return FALSE;

    strcpy(date->str_day, arr_words[0]);
    strcpy(date->str_month, arr_words[1]);
    strcpy(date->str_year, arr_words[2]);

    return TRUE;
}

int is_valid_day(date_t *date)
{
    char *day = date->str_day;
    size_t len = strlen(day);

    for (size_t i = 0; i < len; i++)
    {
        if (!isdigit(day[i]))
            return FALSE;
    }

    int result = 0;
    for (size_t i = 0; i < len; i++)
    {
        result = 10 * result + (day[i] - '0');
    }

    date->int_day = result;

    return TRUE;
}

int is_valid_month(date_t *date)
{
    char month_lower[MAX_STR_SIZE];

    size_t len_str_month = strlen(date->str_month);

    for (size_t i = 0; i < len_str_month; i++)
        month_lower[i] = tolower(date->str_month[i]);

    month_lower[len_str_month] = '\0';

    for (size_t i = 0; i < MONTH_COUNT; i++)
    {
        if (!strcmp(month_lower, months[i]))
        {
            date->index_month = i;
            return TRUE;
        }
    }

    return FALSE;
}

int is_valid_year(date_t *date)
{
    char *year = date->str_year;
    size_t len = strlen(year);

    for (size_t i = 0; i < len; i++)
    {
        if (!isdigit(year[i]))
            return FALSE;
    }

    int result = 0;
    for (size_t i = 0; i < len; i++)
    {
        result = 10 * result + (year[i] - '0');
    }

    if (result == 0)
        return FALSE;

    date->int_year = result;

    return TRUE;
}

int is_valid_date(date_t *date)
{
    if (!is_valid_day(date))
        return FALSE;

    if (!is_valid_month(date))
        return FALSE;

    if (!is_valid_year(date))
        return FALSE;

    if ((date->int_year % 4 == 0 && date->int_year % 100 != 0) || (date->int_year % 400 == 0))
        days_in_months[1] = 29;

    if ((date->int_day > 0) && (date->int_day <= days_in_months[date->index_month]))
        return TRUE;

    return FALSE;
}

int main(void)
{
    char str[MAX_STR_SIZE];
    size_t len_str = 0;
    
    int error;

    error = read_str(str, &len_str);
    if (error != EXIT_SUCCESS)
        return error;

    date_t date;

    int answer;

    answer = is_init_date(str, &date);
    if (answer != TRUE)
    {
        printf("NO\n");
        return EXIT_SUCCESS;
    }

    answer = is_valid_date(&date);
    if (answer != TRUE)
    {
        printf("NO\n");
        return EXIT_SUCCESS;
    }

    printf("YES\n");
    
    return EXIT_SUCCESS;
}
