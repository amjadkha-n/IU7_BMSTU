#include <stdio.h>
#include <string.h>

#include "my_string_len.h"

int main(void)
{
    setbuf(stdout, NULL);

    printf("Len of %s%ld\n", "hello is ", my_asm_len("hello"));

    char buff_1[] = "hellooooooworlddddddddd";
    char buff_2[] = "ddddddddddddddddddddddd";

    my_asm_copy(buff_1 + 5, buff_2, 10);

    printf("%s\n", buff_1);

    return OK;
}