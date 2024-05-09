#include "big_float.h"

// Function to print a bigfloat.
void print_bigfloat(bigfloat_t *a) 
{
    int mantisse_end = 0;
    if (a->is_negative == 1)
        printf("-"); // Print a minus sign if the bigfloat is negative.
    if (a->mantisse_len == 0) {
        printf("0"); // Print '0' if the bigfloat has no mantisse.
        return;
    }
    printf("0."); // Print the decimal point.
    for (; mantisse_end < a->mantisse_len && a->mantisse[mantisse_end] == 0; mantisse_end++);
    for (int i = a->mantisse_len - 1; i >= mantisse_end; i--)
        printf("%d", a->mantisse[i]); // Print each digit of the mantisse.
    printf(" E %d", a->order); // Print the order.
}

// Function to convert a string to a bigfloat.
int str_to_bigfloat(bigfloat_t *a, char str[]) 
{
    int i = 0;
    int point_cnt = 0, extra_order = 0, spaces_cnt = 0, last_zeros_cnt = 0;
    char *order_end;

    if (strlen(str) == 0)
        return 1; // Return 1 for an empty string.

    // Determine the sign of the bigfloat.
    if (str[0] == '-') 
    {
        a->is_negative = 1;
        i = 1;
    }
    else if (str[0] == '+')
        i = 1;

    // Read leading zeros and decimal point.
    for (; str[i] == '0' || str[i] == '.'; i++) 
    {
        if (point_cnt == 1)
            extra_order--; // Adjust the order for decimal point.
        if (str[i] == '.')
            point_cnt++;
        if (point_cnt > 1)
            return 1; // Return 1 for multiple decimal points.
    }

    // Calculate the size of the mantisse.
    for (; str[i] != '\0' && str[i] != 'e' && str[i] != 'E' && str[i] != ' '; i++)
    {
        if (str[i] == '.')
        {
            point_cnt++;
            if (point_cnt > 1)
                return 1; // Return 1 for multiple decimal points.
            continue;
        }
        else if (!isdigit(str[i]))
            return 1; // Return 1 for non-numeric characters.
        if (point_cnt == 0)
            extra_order++;
        a->mantisse_len++;
    }

    // Check for trailing zeros in the mantisse.
    if (point_cnt == 1)
        for (;str[i - last_zeros_cnt - 1] == '0'; last_zeros_cnt++);
    a->mantisse_len -= last_zeros_cnt;
    if (a->mantisse_len < 0)
        a->mantisse_len = 0;

    if (a->mantisse_len >= MAX_MANTISSE_LEN)
        return 2; // Return 2 for mantisse exceeding MAX_MANTISSE_LEN.
    a->order = extra_order;

    // Skip extra spaces.
    for(; str[i] == ' '; i++, spaces_cnt++);
    
    // Read the order if present.
    if (str[i] != '\0')
    {
        spaces_cnt++;
        if (str[i] != 'e' && str[i] != 'E')
            return 1; // Return 1 for invalid exponent format.
        i++;
        for(; str[i] == ' '; i++, spaces_cnt++);
        if (!isdigit(str[i]) && str[i] != '+' && str[i] != '-')
            return 1; // Return 1 for invalid exponent format.
        if (a->mantisse_len == 0 && i == 1)
            return 3; // Return 3 for missing mantisse.
        a->order += strtol(&str[i], &order_end, 10); // Convert exponent to integer.
        if (*order_end != '\0')
            return 1; // Return 1 for invalid exponent format.
    }
    i = i - spaces_cnt - 1 - last_zeros_cnt;

    // Read the mantisse.
    for (int j = 0; j <= a->mantisse_len; j++) 
    {
        if (str[i - j] == '.') 
        {
            i--;
            j--;
        }
        else
            a->mantisse[j] = str[i - j] - '0'; // Convert character to integer and store it.
    }
    return 0; // Return 0 for success.
}

// Function to compare two bigfloats.
int cmp_bigfloat(bigfloat_t *a, bigfloat_t *b) 
{
    if (a->is_negative != b->is_negative)
        return 1; // Return 1 if signs are different.
    if (a->order != b->order)
        return 2; // Return 2 if orders are different.
    if (a->mantisse_len != b->mantisse_len)
        return 3; // Return 3 if mantisse lengths are different.
    for (int i = 0; i < a->mantisse_len; i++)
        if (a->mantisse[i] != b->mantisse[i])
            return 4; // Return 4 if mantisse digits are different.
    return 0; // Return 0 for equality.
}
