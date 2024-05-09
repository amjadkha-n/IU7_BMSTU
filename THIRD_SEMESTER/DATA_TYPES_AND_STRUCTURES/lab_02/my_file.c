#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "my_file.h"

#define SCAN_ERROR 2
#define EPS 1e-8
/**
 * @brief Scan student information from the user.
 *
 * This function prompts the user to enter information about a student, including
 * their name, last name, group number, gender, age, average score, admission date,
 * and address details based on the type of address (house, dormitory, or rented apartment).
 *
 * @param st Pointer to a 'student' structure where the scanned information will be stored.
 * @return Returns EXIT_SUCCESS on successful scanning, and SCAN_ERROR on any error during input.
 */
int scan_student(student *st)
{
    int buf;

    printf("Enter the Last Name (up to 20 characters): ");
    if ((fgets(st->surname, SURNAME_MAX + 1, stdin) == NULL) || ((st->surname[strlen(st->surname) - 1] != '\n') && (strlen(st->surname) == SURNAME_MAX)))
        return SCAN_ERROR;
    if (st->surname[strlen(st->surname) - 1] == '\n')
        st->surname[strlen(st->surname) - 1] = '\0';

    printf("Enter the name(up to 7 characters): ");
    if ((fgets(st->name, NAME_MAX + 1, stdin) == NULL) || ((st->name[strlen(st->name) - 1] != '\n') && (strlen(st->name) == NAME_MAX)))
        return SCAN_ERROR;
    if (st->name[strlen(st->name) - 1] == '\n')
        st->name[strlen(st->name) - 1] = '\0';

    printf("Enter the group number (positive integer): ");
    if ((scanf("%d", &st->group) != 1) || (st->group <= 0))
    {
        setbuf(stdin, NULL);
        return SCAN_ERROR;
    }

    printf("Enter gender(0-male, 1-female): ");
    if ((scanf("%d", &buf) != 1) || ((buf != 0) && (buf != 1)))
    {
        setbuf(stdin, NULL);
        return SCAN_ERROR;
    }
    st->gnd = buf;

    printf("Enter the age (positive integer): ");
    if ((scanf("%d", &st->age) != 1) || (st->age <= 0))
    {
        setbuf(stdin, NULL);
        return SCAN_ERROR;
    }

    printf("Enter the average score (real number): ");
    if ((scanf("%lf", &st->average_mark) != 1) || (st->average_mark < 0))
    {
        setbuf(stdin, NULL);
        return SCAN_ERROR;
    }

    printf("Enter the admission date:\n");
    printf("Enter the day (an integer from 1 to 31 inclusive): ");
    if (scanf("%d", &st->data.day) != 1 || st->data.day <= 0 || st->data.day > 31)
    {
        setbuf(stdin, NULL);
        return SCAN_ERROR;
    }

    printf("Enter the month (an integer from 1 to 12 inclusive): ");
    if ((scanf("%d", &st->data.month) != 1) || (st->data.month <= 0) || (st->data.month > 12))
    {
        setbuf(stdin, NULL);
        return SCAN_ERROR;
    }

    printf("Enter the year (an integer from 0 to 2023 inclusive: ");
    if ((scanf("%d", &st->data.year) != 1) || (st->data.year <= 0) || (st->data.year > 2023))
    {
        setbuf(stdin, NULL);
        return SCAN_ERROR;
    }

    printf("Enter the type of addressa(0 - house, 1 - dormitory, 2 - rented): ");
    if ((scanf("%d", &buf) != 1) || (buf != 0 && buf != 1 && buf != 2))
    {
        setbuf(stdin, NULL);
        return SCAN_ERROR;
    }

    getchar();
    st->type = buf;

    if (st->type == 0)
    {
        printf("Characteristics of the house:\n");
        printf("Enter the street name (up to 20 characters): ");
        if ((fgets(st->choice.bld.street, STREET_MAX + 1, stdin) == NULL) || ((st->choice.bld.street[strlen(st->choice.bld.street)] != '\n') && (strlen(st->choice.bld.street) == STREET_MAX)))
            return SCAN_ERROR;
        if (st->choice.bld.street[strlen(st->choice.bld.street) - 1] == '\n')
            st->choice.bld.street[strlen(st->choice.bld.street) - 1] = '\0';

        printf("Enter the house number (an integer greater than 0): ");
        if ((scanf("%d", &st->choice.bld.build_number) != 1) || (st->choice.bld.build_number <= 0))
        {
            setbuf(stdin, NULL);
            return SCAN_ERROR;
        }
        printf("Enter the apartment number (an integer greater than 0): ");
        if ((scanf("%d", &st->choice.bld.flat_number) != 1) || (st->choice.bld.flat_number <= 0))
        {
            setbuf(stdin, NULL);
            return SCAN_ERROR;
        }
    }
    else if (st->type == 1)
    {
        printf("Characteristics of the hostel:\n");
        printf("Enter the dorm number (an integer greater than 0): ");
        if ((scanf("%d", &st->choice.hst.host_number) != 1) || (st->choice.hst.host_number <= 0))
        {
            setbuf(stdin, NULL);
            return SCAN_ERROR;
        }

        printf("Enter the room number (an integer greater than 0): ");
        if ((scanf("%d", &st->choice.hst.room_number) != 1) || (st->choice.hst.room_number <= 0))
        {
            setbuf(stdin, NULL);
            return SCAN_ERROR;
        }
    }
    else if (st->type == 2)
    {
        printf("Characteristics of a rented apartment:\n");
        printf("Enter the street name (up to 20 characters): ");
        if ((fgets(st->choice.rnt.street, STREET_MAX + 1, stdin) == NULL) || ((st->choice.rnt.street[strlen(st->choice.rnt.street)] != '\n') && (strlen(st->choice.rnt.street) == STREET_MAX)))
            return SCAN_ERROR;
        if (st->choice.rnt.street[strlen(st->choice.rnt.street) - 1] == '\n')
            st->choice.rnt.street[strlen(st->choice.rnt.street) - 1] = '\0';

        printf("Enter the house number (an integer greater than 0): ");
        if ((scanf("%d", &st->choice.rnt.build_number) != 1) || (st->choice.rnt.build_number <= 0))
        {
            setbuf(stdin, NULL);
            return SCAN_ERROR;
        }

        printf("Enter the apartment number (an integer greater than 0): ");
        if ((scanf("%d", &st->choice.rnt.flat_number) != 1) || (st->choice.rnt.flat_number <= 0))
        {
            setbuf(stdin, NULL);
            return SCAN_ERROR;
        }

        printf("Enter the cost of the apartment (an integer number of millions is greater than or equal to 0): ");
        if ((scanf("%d", &st->choice.rnt.cost) != 1) || (st->choice.rnt.cost < 0))
        {
            setbuf(stdin, NULL);
            return SCAN_ERROR;
        }
    }

    getchar();
    return EXIT_SUCCESS;
}

int scan_student_file(student *st, FILE *f)
{
    int buf;

    if ((fgets(st->surname, SURNAME_MAX + 1, f) == NULL) || ((st->surname[strlen(st->surname) - 1] != '\n') && (strlen(st->surname) == NAME_MAX)))
        return SCAN_ERROR;
    if (st->surname[strlen(st->surname) - 1] == '\n')
        st->surname[strlen(st->surname) - 1] = '\0';

    if ((fgets(st->name, NAME_MAX + 1, f) == NULL) || ((st->name[strlen(st->name) - 1] != '\n') && (strlen(st->name) == NAME_MAX)))
        return SCAN_ERROR;
    if (st->name[strlen(st->name) - 1] == '\n')
        st->name[strlen(st->name) - 1] = '\0';

    if ((fscanf(f, "%d", &st->group) != 1) || (st->group <= 0))
        return SCAN_ERROR;

    if ((fscanf(f, "%d", &buf) != 1) || ((buf != 0) && (buf != 1)))
        return SCAN_ERROR;

    st->gnd = buf;

    if ((fscanf(f, "%d", &st->age) != 1) || (st->age <= 0))
        return SCAN_ERROR;

    if ((fscanf(f, "%lf", &st->average_mark) != 1) || (st->average_mark < 0))
        return SCAN_ERROR;

    if ((fscanf(f, "%d", &st->data.day) != 1) || (st->data.day <= 0) || (st->data.day > 31))
        return SCAN_ERROR;

    if ((fscanf(f, "%d", &st->data.month) != 1) || (st->data.month <= 0) || (st->data.month > 12))
        return SCAN_ERROR;

    if ((fscanf(f, "%d", &st->data.year) != 1) || (st->data.year <= 0) || (st->data.year > 2023))
        return SCAN_ERROR;

    if ((fscanf(f, "%d\n", &buf) != 1) || (buf != 0 && buf != 1 && buf != 2))
        return SCAN_ERROR;

    st->type = buf;

    if (st->type == 0)
    {
        if ((fgets(st->choice.bld.street, STREET_MAX + 1, f) == NULL) || ((st->choice.bld.street[strlen(st->choice.bld.street)] != '\n') && (strlen(st->choice.bld.street) == STREET_MAX)))
            return SCAN_ERROR;
        if (st->choice.bld.street[strlen(st->choice.bld.street) - 1] == '\n')
            st->choice.bld.street[strlen(st->choice.bld.street) - 1] = '\0';

        if ((fscanf(f, "%d", &st->choice.bld.build_number) != 1) || (st->choice.bld.build_number <= 0))
            return SCAN_ERROR;

        if ((fscanf(f, "%d", &st->choice.bld.flat_number) != 1) || (st->choice.bld.flat_number <= 0))
            return SCAN_ERROR;
    }
    else if (st->type == 1)
    {
        if ((fscanf(f, "%d", &st->choice.hst.host_number) != 1) || (st->choice.hst.host_number <= 0))
            return SCAN_ERROR;

        if ((fscanf(f, "%d", &st->choice.hst.room_number) != 1) || (st->choice.hst.room_number <= 0))
            return SCAN_ERROR;
    }
    else if (st->type == 2)
    {
        if ((fgets(st->choice.rnt.street, STREET_MAX + 1, f) == NULL) || ((st->choice.rnt.street[strlen(st->choice.rnt.street)] != '\n') && (strlen(st->choice.rnt.street) == STREET_MAX)))
            return SCAN_ERROR;
        if (st->choice.rnt.street[strlen(st->choice.rnt.street) - 1] == '\n')
            st->choice.rnt.street[strlen(st->choice.rnt.street) - 1] = '\0';

        if ((fscanf(f, "%d", &st->choice.rnt.build_number) != 1) || (st->choice.rnt.build_number <= 0))
            return SCAN_ERROR;

        if ((fscanf(f, "%d", &st->choice.rnt.flat_number) != 1) || (st->choice.rnt.flat_number <= 0))
            return SCAN_ERROR;

        if ((fscanf(f, "%d", &st->choice.rnt.cost) != 1) || (st->choice.rnt.cost < 0))
            return SCAN_ERROR;

    }
    fscanf(f, " ");

    return EXIT_SUCCESS;
}
/**
 * @brief Scan student information from a file.
 *
 * This function reads information about a student from a given file stream and populates
 * the corresponding fields in the 'student' structure. It expects the file stream to contain
 * the student details in a specific format.
 *
 * @param st Pointer to a 'student' structure where the scanned information will be stored.
 * @param f File stream from which to read the student information.
 * @return Returns EXIT_SUCCESS on successful scanning, and SCAN_ERROR on any error during input.
 */
int read_array_of_st(student array[STUDENT_MAX], size_t *size, FILE *f)
{
    size_t i = 0;
    while (scan_student_file(&array[i], f) == EXIT_SUCCESS)
    {
        i++;
        if (i > STUDENT_MAX)
            return EXIT_FAILURE;
    }
    *size = i;
    if (i == 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

/**
 * @brief Print the header for displaying student information.
 *
 * This function prints a formatted header for displaying student information,
 * including columns for various attributes such as name, surname, group, gender, etc.
 * The format is designed for clear and organized presentation.
 */
void print_head(void)
{
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n");
    printf("| N  |%-20s|%-7s|group|Gender|Age   |Aver Mark |Year      |Type     |%-20s|building  |hostel    |room      |flat      |Cost      |\n", "Surname", "Name", "Street");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n");
}
/**
 * @brief Print formatted information of a student.
 *
 * This function prints the details of a student in a formatted manner,
 * including the student's index, name, surname, group, gender, age, average mark,
 * admission date, and address details based on the type of address (house, hostel, or rented apartment).
 *
 * @param st Pointer to a 'student' structure containing the student information.
 * @param index Index of the student in the list.
 */
void print_student(student *st, size_t index)
{
    printf("|%-4zu|", index);
    printf("%-20s|", st->surname);
    printf("%-7s|", st->name);
    printf("%-5d|", st->group);
    if (st->gnd == male)
        printf("male  |");
    else
        printf("female|");
    printf("%-6d|", st->age);
    printf("%-10lf|", st->average_mark);
    printf("%2d.%2d.%4d|", st->data.day, st->data.month, st->data.year);
    if (st->type == house)
    {
        printf("House    |");
        printf("%-20s|", st->choice.bld.street);
        printf("%-10d|", st->choice.bld.build_number);
        printf("----------|");
        printf("----------|");
        printf("%-10d|", st->choice.bld.flat_number);
        printf("----------|\n");
    }
    else if(st->type == dorm)
    {
        printf("Hostel   |");
        printf("%-20s|", "--------------------");
        printf("----------|");
        printf("%-10d|", st->choice.hst.host_number);
        printf("%-10d|", st->choice.hst.room_number);
        printf("----------|");
        printf("----------|\n");
    }
    else
    {
        printf("Rent     |");
        printf("%-20s|", st->choice.rnt.street);
        printf("%-10d|", st->choice.rnt.build_number);
        printf("----------|");
        printf("----------|");
        printf("%-10d|", st->choice.rnt.flat_number);
        printf("%-10d|\n", st->choice.rnt.cost);
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n");
}
/**
 * @brief Perform bubble sort on an array of students based on their average marks.
 *
 * This function sorts an array of student structures in ascending order based on
 * the students' average marks using the bubble sort algorithm.
 *
 * @param array An array of 'student' structures to be sorted.
 * @param size The number of elements in the array.
 */
void table_bubble_sort(student array[STUDENT_MAX], size_t size)
{
    student tmp;
    for (size_t i = 0; i < size - 1; i++)
        for (size_t j = 0; j < size - 1; j++)
            if (array[j].average_mark > array[j + 1].average_mark)
            {
                tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
}
/**
 * @brief Compare function for sorting students based on their average marks.
 *
 * This function is designed to be used as a comparison function for sorting an array
 * of student structures. It compares two students based on their average marks and
 * returns an integer indicating their relative order in the sorted sequence.
 *
 * @param p Pointer to the first 'student' structure.
 * @param q Pointer to the second 'student' structure.
 * @return Returns 0 if average marks are equal, 1 if the average mark of 'p' is greater than 'q',
 *         and -1 if the average mark of 'p' is less than 'q'.
 */
int compare_student(const void *p, const void *q)
{
    const student *a = p;
    const student *b = q;

    if (fabs((a->average_mark) - (b->average_mark)) < EPS)
        return 0;
    else if (a->average_mark > b->average_mark)
        return 1;
    else
        return -1;
}

/**
 * @brief Perform quicksort on an array of students based on their average marks.
 *
 * This function utilizes the `qsort` function to perform quicksort on an array of
 * student structures. The sorting is done based on the students' average marks.
 *
 * @param array An array of 'student' structures to be sorted.
 * @param size The number of elements in the array.
 */
void quick_sort_main(student array[STUDENT_MAX], size_t size)
{
    qsort(array, size, sizeof(array[0]), compare_student);
}

/**
 * @brief Delete students from an array based on their average marks.
 *
 * This function removes students from an array whose average marks differ by less than
 * a small epsilon value from the specified average mark. It updates the array and its size accordingly.
 *
 * @param array An array of 'student' structures to be modified.
 * @param size Pointer to the size of the array, updated to reflect the new size after deletion.
 * @param aver The average mark used as a threshold for deletion.
 */
void delete_st_by_aver(student array[STUDENT_MAX], size_t *size, double aver)
{
    student *pb = array;

    for (student *p = array; p < array + *size; p++)
    {
        if (fabs(p->average_mark - aver) > EPS)
        {
            *pb = *p;
            pb++;
        }
    }
    *size = pb - array;
}

/**
 * @brief Create a key table from an array of students based on average marks.
 *
 * This function creates a key table, where each element contains the average mark
 * and the corresponding index of a student in the original array. The key table is based
 * on an array of student structures.
 *
 * @param st An array of 'student' structures.
 * @param size The number of elements in the array.
 * @param k An array of 'key' structures to store the generated keys.
 */
void create_key_table(student st[STUDENT_MAX], size_t size, key k[STUDENT_MAX])
{
    for (size_t i = 0; i < size; i++)
    {
        k[i].average = st[i].average_mark;
        k[i].index = i;
    }
}
/**
 * @brief Perform bubble sort on an array of keys based on average marks.
 *
 * This function sorts an array of key structures in ascending order based on
 * the average marks of the corresponding students using the bubble sort algorithm.
 *
 * @param array An array of 'key' structures to be sorted.
 * @param size The number of elements in the array.
 */

void key_bubble_sort(key array[STUDENT_MAX], size_t size)
{
    key tmp;
    for (size_t i = 0; i < size - 1; i++)
        for (size_t j = 0; j < size - 1; j++)
            if (array[j].average > array[j + 1].average)
            {
                tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
}

/**
 * @brief Compare function for sorting keys based on average marks.
 *
 * This function is designed to be used as a comparison function for sorting an array
 * of key structures. It compares two keys based on their average marks and
 * returns an integer indicating their relative order in the sorted sequence.
 *
 * @param p Pointer to the first 'key' structure.
 * @param q Pointer to the second 'key' structure.
 * @return Returns 0 if average marks are equal, 1 if the average mark of 'p' is greater than 'q',
 *         and -1 if the average mark of 'p' is less than 'q'.
 */
int compare_key(const void *p, const void *q)
{
    const key *a = p;
    const key *b = q;

    if (fabs((a->average) - (b->average)) < EPS)
        return 0;
    else if (a->average > b->average)
        return 1;
    else
        return -1;
}

/**
 * @brief Perform quicksort on an array of keys based on average marks.
 *
 * This function utilizes the `qsort` function to perform quicksort on an array of
 * key structures. The sorting is done based on the average marks of the corresponding students.
 *
 * @param array An array of 'key' structures to be sorted.
 * @param size The number of elements in the array.
 */
void quick_sort_key(key array[STUDENT_MAX], size_t size)
{
    qsort(array, size, sizeof(array[0]), compare_key);
}

/**
 * @brief Print information of students who rented apartments in a specific year.
 *
 * This function prints the details of students who rented apartments in a specified year
 * from an array of student structures. It utilizes the `print_head` and `print_student` functions
 * for consistent and formatted output.
 *
 * @param st An array of 'student' structures.
 * @param size The number of elements in the array.
 * @param year The specific year for filtering students.
 * @return Returns EXIT_SUCCESS if at least one student is found and printed, and EXIT_FAILURE otherwise.
 */
int print_my_students(student st[STUDENT_MAX], size_t size, int year)
{
    int flag = 0;

    for (size_t i = 0; i < size; i++)
    {
        if ((st[i].data.year == year) && (st[i].type == rent))
        {
            if (flag == 0)
                print_head();
            flag = 1;
            print_student(&st[i], i);
        }
    }

    if (flag == 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/**
 * @brief Print a table of keys containing indices and average marks.
 *
 * This function prints a table of keys, where each row represents an index and the
 * corresponding average mark. It provides a clear representation of the key structure.
 *
 * @param k An array of 'key' structures.
 * @param size The number of elements in the array.
 */
void print_key_table(key k[STUDENT_MAX], size_t size)
{
    printf("| N  |  Average |\n");
    for (size_t i = 0; i < size; i++)
    {
        printf("|%4zu|%10.6lf|\n", k[i].index, k[i].average);
    }
}

/**
 * @brief Copy an array of students to another array.
 *
 * This function copies the contents of one array of student structures to another array.
 *
 * @param src The source array of 'student' structures.
 * @param dst The destination array of 'student' structures.
 * @param size The number of elements to copy from the source array.
 */
void copy_students(student src[STUDENT_MAX], student dst[STUDENT_MAX], size_t size)
{
    for (size_t i = 0; i < size; i++)
        dst[i] = src[i];
}

/**
 * @brief Copy an array of keys to another array.
 *
 * This function copies the contents of one array of key structures to another array.
 *
 * @param src The source array of 'key' structures.
 * @param dst The destination array of 'key' structures.
 * @param size The number of elements to copy from the source array.
 */
void copy_keys(key src[STUDENT_MAX], key dst[STUDENT_MAX], size_t size)
{
    for (size_t i = 0; i < size; i++)
        dst[i] = src[i];
}

/**
 * @brief Perform time and memory calculations for sorting operations on student and key arrays.
 *
 * This function measures the execution time of bubble sort and quicksort algorithms on both
 * the student and key arrays. Additionally, it calculates and compares memory usage for the two arrays.
 * The results are printed for analysis.
 *
 * @param st An array of 'student' structures.
 * @param k An array of 'key' structures.
 * @param size Pointer to the number of elements in the arrays.
 */
void time_calculations(student st[STUDENT_MAX], key k[STUDENT_MAX], size_t *size)
{
    student st_temp[STUDENT_MAX];
    key key_temp[STUDENT_MAX];
    unsigned long long a;

    copy_keys(k, key_temp, *size);
    copy_students(st, st_temp, *size);

    clock_t bubble_table_time_b = clock();
    table_bubble_sort(st_temp, *size);
    clock_t bubble_table_time_e = clock();

    copy_students(st, st_temp, *size);

    clock_t bubble_key_time_b = clock();
    key_bubble_sort(key_temp, *size);
    clock_t bubble_key_time_e = clock();

    copy_keys(k, key_temp, *size);

    clock_t quick_table_time_b = clock();
    quick_sort_main(st_temp, *size);
    clock_t quick_table_time_e = clock();

    copy_students(st, st_temp, *size);

    clock_t quick_key_time_b = clock();
    quick_sort_key(key_temp, *size);
    clock_t quick_key_time_e = clock();

    double bubble_table_time = (double) (bubble_table_time_e - bubble_table_time_b) / CLOCKS_PER_SEC;
    double bubble_key_time = (double) (bubble_key_time_e - bubble_key_time_b) / CLOCKS_PER_SEC;
    double quick_table_time = (double) (quick_table_time_e - quick_table_time_b) / CLOCKS_PER_SEC;
    double quick_key_time = (double) (quick_key_time_e - quick_key_time_b) / CLOCKS_PER_SEC;


    printf("\nSorting %zu records\n", *size);
    printf("Time:\n");
    printf("----------------------------------------\n");
    printf("|            | bubble,ms  |  quick,ms  |\n");
    printf("----------------------------------------\n");
    printf("|Table       |%10.3lf  |%10.3lf  |\n", bubble_table_time * 1000, quick_table_time * 1000);
    printf("----------------------------------------\n");
    printf("|Key table   |%10.3lf  |%10.3lf  |\n", bubble_key_time * 1000, quick_key_time * 1000);
    printf("----------------------------------------\n");
    printf("\n");
    printf("Memory:\n");
    printf("-----------------------------------------\n");
    printf("|                  |  memory,b          |\n");
    printf("-----------------------------------------\n");
    printf("|Table             |%-20zu|\n", sizeof(st[0]) * (*size));
    printf("-----------------------------------------\n");
    printf("|Key table         |%-20zu|\n", sizeof(k[0]) * (*size));
    printf("-----------------------------------------\n");
    printf("|Key table + table |%-20zu|\n", sizeof(st[0]) * (*size) + sizeof(k[0]) * (*size));
    printf("-----------------------------------------\n");
    printf("\n");

    printf("Bubble sorting by key table is more efficient than by a regular table on %.2lf%%\n",  (bubble_table_time / bubble_key_time) * 100 - 100);
    printf("Quick sorting by key table is more efficient than by the main table on %.2lf%%\n",  (bubble_key_time / quick_key_time) * 100 - 100);
    printf("Memory gain for the main table %zu%%\n", (sizeof(k[0]) * (*size)) / (sizeof(st[0]) * (*size)/ 100));

}
/**
 * @brief Print the menu options for the program.
 *
 * This function prints the menu options for the program, providing a list of operations
 * that the user can choose from.
 */
void print_menu(void)
{
    printf("Menu:\n");
    printf("0) Finish the work\n");
    printf("1) Enter the student record manually (at the end of the table)\n");
    printf("2) Enter information about students from the file (no more than 1000 entries)\n");
    printf("3) Output the table\n");
    printf("4) Sort by average score and output the table\n");
    printf("5) Delete students with the specified grade point average\n");
    printf("6) Find and withdraw students of the specified year of admission living in rented apartments\n");
    printf("7) Create and output a key table for this table\n");
    printf("8) Create and output a key table sorted by average score\n");
    printf("9) Create a table of keys, sort by average score and output the original table from it\n");
    printf("10) Compare the efficiency of the program depending on the sorting and the table that we sort\n");
    printf("Enter the operation number:\n");
}

/**
 * @brief Perform various operations on the student records based on user input.
 *
 * This function provides a menu-driven interface for performing various operations on
 * the student records, such as entering data manually, reading from a file, sorting, deleting,
 * and printing the student records. The user can choose from a range of operations by entering
 * the corresponding operation number.
 *
 * @param st An array of student records.
 * @param size Pointer to the size of the student records array.
 * @return EXIT_SUCCESS on successful execution, EXIT_FAILURE on error, or EXIT to finish the program.
 */
int process(student st[STUDENT_MAX], size_t *size)
{
    FILE *f;
    char file_name[FILE_MAX];
    double av;
    int year;
    key k[STUDENT_MAX];
    print_menu();
    int operation;

    if (scanf("%d", &operation) != 1)
    {
        printf("\nInvalid operation number\n");
        setbuf(stdin, NULL);
        return EXIT_FAILURE;
    }
    getchar();

    if (operation == 0)
        return EXIT;

    else if (operation == 1)
    {
        if (*size == (size_t) STUDENT_MAX)
        {
            printf("\nThere are already 1000 elements in the table\n");
            return EXIT_FAILURE;
        }
        else
        {
            if (scan_student(&st[*size]) != EXIT_SUCCESS)
            {
                printf("\nIncorrect data entered\n");
                return EXIT_SUCCESS;
            }
            else
            {
                printf("\nSuccess\n");
                (*size)++;
            }
            return EXIT_SUCCESS;
        }
    }

    else if (operation == 2)
    {
        printf("Enter the file name (no more than 40 characters):\n");
        if ((fgets(file_name, FILE_MAX, stdin) == NULL) || ((file_name[strlen(file_name) - 1] != '\n') && (strlen(file_name) == NAME_MAX)))
        {
            printf("\nIncorrect file name input\n");
            return EXIT_FAILURE;
        }
        if (file_name[strlen(file_name) - 1] == '\n')
            file_name[strlen(file_name) - 1] = '\0';
        f = fopen(file_name, "r");
        if (f)
        {
            if (read_array_of_st(st, size, f) == EXIT_FAILURE)
                printf("\nIt was not possible to count any structures\n");
            else
                printf("\nSuccessfully read\n");
            fclose(f);
            return EXIT_SUCCESS;
        }
        else
        {
            printf("\nFile not detected\n");
            return EXIT_FAILURE;
        }
    }

    else if (operation == 3)
    {
        if (*size == 0)
        {
            printf("\nThere are no students in the table\n");
            return EXIT_FAILURE;
        }
        print_head();
        for (size_t i = 0; i < *size; i++)
            print_student(&st[i], i + 1);
    }

    else if (operation == 4)
    {
        if (*size == 0)
        {
            printf("\nThere are no students in the table\n");
            return EXIT_FAILURE;
        }
        quick_sort_main(st, *size);
        print_head();
        for (size_t i = 0; i < *size; i++)
            print_student(&st[i], i + 1);
    }

    else if (operation == 5)
    {
        if (*size == 0)
        {
            printf("\nThere are no students in the table\n");
            return EXIT_FAILURE;
        }
        printf("Enter the average score to delete:\n");
        if (scanf("%lf", &av) != 1)
        {
            printf("\nIncorrect average score\n");
            setbuf(stdin, NULL);
            return EXIT_FAILURE;
        }
        delete_st_by_aver(st, size, av);
        printf("\nSuccessful deletion\n");
        return EXIT_SUCCESS;
    }

    else if (operation == 6)
    {
        printf("Enter the year:\n");
        if ((scanf("%d", &year) != 1) || (year <= 0) || (year >2023))
        {
            printf("\nIncorrect year\n");
            setbuf(stdin, NULL);
            return EXIT_FAILURE;
        }
        getchar();
        if (print_my_students(st, *size, year) != EXIT_SUCCESS)
        {
            printf("\nThere are no students with such parameters in the table\n");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    else if (operation == 7)
    {
        if (*size == 0)
        {
            printf("\nThere are no students in the table\n");
            return EXIT_FAILURE;
        }
        create_key_table(st, *size, k);
        printf("Key table:\n");
        print_key_table(k, *size);
    }

    else if (operation == 8)
    {
        if (*size == 0)
        {
            printf("\nThere are no students in the table\n");
            return EXIT_FAILURE;
        }
        create_key_table(st, *size, k);
        quick_sort_key(k, *size);
        printf("Sorted Key Table:\n");
        print_key_table(k, *size);
    }

    else if (operation == 9)
    {
        if (*size == 0)
        {
            printf("\nThere are no students in the table\n");
            return EXIT_FAILURE;
        }
        create_key_table(st, *size, k);
        quick_sort_key(k, *size);
        print_head();
        for (size_t i = 0; i < *size; i++)
            print_student(&st[k[i].index], i + 1);
    }

    else if (operation == 10)
    {
        if (*size == 0)
        {
            printf("\nThere are no students in the table\n");
            return EXIT_FAILURE;
        }

        create_key_table(st, *size, k);
        time_calculations(st, k, size);
    }

    else
        printf("\nInvalid operation number\n");
    return EXIT_SUCCESS;
}
