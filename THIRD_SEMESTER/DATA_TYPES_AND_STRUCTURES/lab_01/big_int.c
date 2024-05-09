#include "big_int.h" // Include the big integer header file.

// Function to print a bigint.
void print_bigint(bigint_t *a)
{
    if (a->is_negative == 1)
        printf("-"); // Print a minus sign if the bigint is negative.
    for(int i = a->data_len - 1; i >= 0; i--)
        printf("%d", a->data[i]); // Print each digit of the bigint in reverse order.
    if (a->data_len == 0)
        printf("0"); // Print '0' if the bigint has no digits.
}

// Function to convert a string to a bigint.
int str_to_bigint(bigint_t *a, char str[]) 
{
    int leading_symbols_count = 0;

    if (strlen(str) == 0)
        return 2; // Return 2 for an empty string.
    if (str[0] == '-') {
        leading_symbols_count = 1; // Skip the negative sign.
        a->is_negative = 1; // Set the bigint as negative.
    }
    else if (str[0] == '+')
        leading_symbols_count = 1; // Skip the positive sign.

    for (; str[leading_symbols_count] == '0'; leading_symbols_count++);
    if (strlen(str) - leading_symbols_count > MAX_INT_LEN)
        return 1; // Return 1 for overflow (bigint length exceeds MAX_INT_LEN).

    for (; a->data_len < (int)strlen(str) - leading_symbols_count; a->data_len++) 
    {
        char current_symbol = *(str + strlen(str) - a->data_len - 1);
        if (!isdigit(current_symbol))
            return 2; // Return 2 for invalid characters in the string.
        a->data[a->data_len] = current_symbol - '0'; // Convert character to integer and store it.
    }
    return 0; // Return 0 for success.
}

// Function to compare two bigints.
int cmp_bigint(bigint_t *a, bigint_t *b) 
{
    if (a->is_negative != b->is_negative)
        return 1; // Return 1 if signs are different.
    if (a->data_len != b->data_len)
        return 2; // Return 2 if lengths are different.
    for (int i = 0; i < a->data_len; i++)
        if (a->data[i] != b->data[i])
            return 3; // Return 3 if digits are different.
    return 0; // Return 0 for equality.
}
