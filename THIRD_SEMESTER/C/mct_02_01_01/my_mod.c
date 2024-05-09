#include <stdio.h>
#include <stdlib.h>
#include "my_mod.h"
#include <string.h>

void add_student()
{
    // Open the file in "ab" mode for appending binary data
    FILE *file = fopen("students.bin", "ab");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }
    // Create a Student structure to store the student's data
    Student student;
    printf("Enter the Surname (5 characters): ");
    scanf("%5s", student.surname);
    getchar();

    if (strlen(student.surname) > 5)
    {
        printf("Please enter less than 6 symbols.\n");
        fclose(file);
        return;
    }
    // getchar();
    printf("Enter the Height (in cm): ");
    scanf("%d", &student.height);
    getchar();
    // Write the student's data to the file
    fwrite(&student, sizeof(Student), 1, file);

    fclose(file);
}

void print_students()
{
    FILE *file = fopen("students.bin", "rb");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }
    Student student;
    // Read and print the data of each student in the file
    while (fread(&student, sizeof(Student), 1, file) == 1)
    {
        printf("Surname: %s, Height: %d cm\n", student.surname, student.height);
    }

    fclose(file);
}

void remove_below_average()
{
    FILE *file = fopen("students.bin", "r+b");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    Student student;
    int total_students = 0, total_height = 0;
    // Calculate the total number of students and the total height
    while (fread(&student, sizeof(Student), 1, file) == 1)
    {
        total_students++;
        total_height += student.height;
    }
    // If there are no students in the file, close the file and return
    if (total_students == 0)
    {
        fclose(file);
        return;
    }

    float average_height = (float)total_height / total_students;
    // Move the file position indicator to the beginning of the file
    rewind(file);

    FILE *temp_file = fopen("temp.bin", "wb");
    if (temp_file == NULL)
    {
        printf("Error creating the temporary file.\n");
        fclose(file);
        return;
    }
     // Iterate through each student in the file
    while (fread(&student, sizeof(Student), 1, file) == 1)
    {
        if (student.height >= average_height)
        {
            fwrite(&student, sizeof(Student), 1, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove("students.bin");
    rename("temp.bin", "students.bin");
}

void sort_students()
{
    FILE *file = fopen("students.bin", "r+b");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }

    Student students[100];
    int total_students = 0;
    // Read each student from the file and store them in the students array
    while (fread(&students[total_students], sizeof(Student), 1, file) == 1)
    {
        total_students++;
    }

    // bubble sort
    for (int i = 0; i < total_students - 1; i++)
    {
        for (int j = 0; j < total_students - i - 1; j++)
        {
            if (students[j].height > students[j + 1]. height)
            {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    rewind(file);
    // Write the sorted students array back to the file
    fwrite(students, sizeof(Student), total_students, file);

    fclose(file);
}

void erase_data()
{
    FILE *file = fopen("students.bin", "wb");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    fclose(file);
}