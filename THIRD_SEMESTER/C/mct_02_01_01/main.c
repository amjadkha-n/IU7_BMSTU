#include <stdio.h>
#include "my_mod.h"

int main()
{
    int choice;

    do 
    {
        printf("\n1. Add Student\n");
        printf("2. Print all Students\n");
        printf("3. Remove Students below average height\n");
        printf("4. Sort Students by height\n");
        printf("5. Erase the data from the bin file\n");
        printf("6. Exit\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                add_student();
                break;
            case 2:
                print_students();
                break;
            case 3:
                remove_below_average();
                break;
            case 4:
                sort_students();
                break;
            case 5:
                erase_data();
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please choose between 1 and 6.\n");

        }   
    }
    while (choice != 6);

    return 0;
}
