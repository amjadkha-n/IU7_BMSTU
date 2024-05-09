#include "operations.h"
#include "big_int.h"

// Function to read a string from user input and handle newline character.
int read_str(char *s, size_t max_len)
{
    if (fgets(s, max_len, stdin) == NULL) // Read a string from input.
        return 1;
     // Check if the last character is a newline.
    if (s[strlen(s) - 1] == '\n')
     // Replace the newline character with null terminator.
        s[strlen(s) - 1] = '\0';
    else
        return 1;
    return 0;
}

// Function to round a bigint.
void round_number(bigint_t *a) 
{
    int first_digit = a->data[0]; // Get the first digit of the bigint.
    a->data_len--; // Decrease the length of the bigint.
    for (int i = 0; i < a->data_len; i++)
        a->data[i] = a->data[i + 1]; // Shift digits to the left.
    if (first_digit >= 5)
    { // Check if the first digit is greater than or equal to 5.
        int extra_digit = 1; // Initialize an extra digit for rounding.
        for (int i = 0; i < a->data_len; i++) 
        {
            int current_number = a->data[i] + extra_digit; // Add the extra digit.
            extra_digit = current_number / BASE; // Calculate the carry.
            current_number %= BASE; // Calculate the new digit.
            a->data[i] = current_number; // Update the digit.
        }
        if (extra_digit > 0)
            a->data[a->data_len++] = extra_digit; // Add the extra digit if needed.
    }
}

// Function to copy one bigint to another.
void bigint_cpy(bigint_t *a, bigint_t *b) 
{
    a->is_negative = b->is_negative; // Copy the sign.
    for (a->data_len = 0; a->data_len < b->data_len; a->data_len++)
        a->data[a->data_len] = b->data[a->data_len]; // Copy the digits.
}

// Function to multiply a bigint by a single digit.
void bigint_to_digit_multiplication(bigint_t *res, bigint_t *a, int b) 
{
    int extra_digit = 0; // Initialize an extra digit for multiplication.
    res->is_negative = a->is_negative; // Copy the sign.

    for (; res->data_len < a->data_len; res->data_len++)
    {
        int current_number = a->data[res->data_len] * b + extra_digit; // Multiply and add the extra digit.
        extra_digit = current_number / BASE; // Calculate the carry.
        res->data[res->data_len] = current_number % BASE; // Calculate the new digit.
    }

    if (extra_digit > 0)
    {
        res->data_len++;
        res->data[res->data_len - 1] = extra_digit; // Add the extra digit if needed.
    }

    if (b == 0)
        res->data_len = 0; // Handle the case where the multiplier is 0.
}

// Function to add two bigints.
void bigint_sum(bigint_t *res, bigint_t *a, bigint_t *b, int extra_zeros_count)
{
    int extra_digit = 0;

    if (b->data_len == 0)
        bigint_cpy(res, a); // If b is zero, copy a to res.
    else 
    {
        for (int i = 0; i < extra_zeros_count; i++)
            res->data[res->data_len++] = a->data[i]; // Add extra zeros if needed.

        for (; res->data_len - extra_zeros_count < b->data_len; res->data_len++) 
        {
            int current_number;
            if (res->data_len < a->data_len)
                current_number = a->data[res->data_len] + b->data[res->data_len - extra_zeros_count] + extra_digit;
            else
                current_number = b->data[res->data_len - extra_zeros_count] + extra_digit;
            extra_digit = current_number / BASE; // Calculate the carry.
            res->data[res->data_len] = current_number % BASE; // Calculate the new digit.
        }

        if (extra_digit > 0)
            res->data[res->data_len++] = extra_digit; // Add the extra digit if needed.
    }
}

// Function to perform multiplication of a bigint and a bigfloat.
int bigint_to_bigfloat_multiplication(bigfloat_t *res, bigint_t *a, bigfloat_t *b) 
{
    bigint_t all_sum = {.data = {0}, .data_len = 0}; // Initialize a bigint for sum.

    // Multiply numbers in the mantissa.
    bigint_to_digit_multiplication(&all_sum, a, b->mantisse[0]);
    for (int i = 1; i < b->mantisse_len; i++) 
    {
        bigint_t cur_element = {.data = {0}, .data_len = 0};
        bigint_t cur_sum = {.data = {0}, .data_len = 0};

        bigint_to_digit_multiplication(&cur_element, a, b->mantisse[i]);
        bigint_sum(&cur_sum, &all_sum, &cur_element, i);
        bigint_cpy(&all_sum, &cur_sum);
    }

    res->is_negative = (!!a->is_negative + !!b->is_negative) % 2; // Determine the sign of the result.
    res->order = all_sum.data_len + b->order - b->mantisse_len; // Calculate the order of the result.

    if (res->order < -99999 || res->order > 99999)
        return 1; // Return an error code if the order is out of range.

    // Round the result and truncate if necessary.
    if (all_sum.data_len > MAX_OUTPUT_LEN) 
    {
        int diff = all_sum.data_len - MAX_OUTPUT_LEN - 1;
        if (diff != 0) 
        {
            for (int i = 0; i < all_sum.data_len - diff; i++)
                all_sum.data[i] = all_sum.data[i + diff]; // Shift data to the left.
            all_sum.data_len = MAX_OUTPUT_LEN + 1; // Update the data length.
        }
        round_number(&all_sum); // Round the number.
    }

    for (; res->mantisse_len < all_sum.data_len; res->mantisse_len++)
        res->mantisse[res->mantisse_len] = all_sum.data[res->mantisse_len]; // Copy data to the result mantissa.

    return 0; // Return 0 for success.
}
