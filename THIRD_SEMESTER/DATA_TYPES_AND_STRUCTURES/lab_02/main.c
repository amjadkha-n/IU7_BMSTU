#include <stdlib.h>
#include <string.h>
#include "my_file.h"
/**
 * @brief The main function to execute the student records processing program.
 *
 * This function initializes an array of student records and a variable to keep track of the
 * current size of the records. It enters a loop where the user is prompted to choose various
 * operations on the student records through the `process` function until the user decides
 * to finish the program.
 *
 * @return 0 on successful execution.
 */
int main(void)
{
    student st[STUDENT_MAX];
    size_t size = 0;

    while (1)
    {
        if (process(st, &size) == EXIT)
            break;
    }

    return 0;
}