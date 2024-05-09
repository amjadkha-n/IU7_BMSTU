#include "../inc/main.h"

int main(void)
{
    char action[LEN_ACTION + 2];

    if (scanf("%4s", action) != 1)
        return READ_ACTION_ERROR;

    if (action[3] != '\0' || !(strncmp(action, "out", LEN_ACTION) == 0 ||
        strncmp(action, "mul", LEN_ACTION) == 0 ||
        strncmp(action, "sqr", LEN_ACTION) == 0 ||
        strncmp(action, "div", LEN_ACTION) == 0))
    {
        return  INVALID_ACTION_ERROR;
    }

    int rc;
    if (action[0] == 'o')
        rc = display_number_as_list();
    else if (action[0] == 'm')
        rc = multiplication_of_two_numbers();
    else if (action[0] == 's')
        rc = squaring_the_number();
    else if (action[0] == 'd')
        rc = dividing_number_without_rem();
    else
        rc = INVALID_ACTION_ERROR;

    return rc;
}
