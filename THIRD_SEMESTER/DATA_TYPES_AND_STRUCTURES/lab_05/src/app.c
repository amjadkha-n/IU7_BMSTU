#include "../inc/app.h"
#include "../inc/io.h"
#include "../inc/array.h"
#include "../inc/timemem.h"
#include "../inc/list.h"

/**
 * @brief Main function for the simulation and time comparisons program.
 *
 * @return OK if the program runs successfully.
 */
int main()
{
    setbuf(stdout, NULL);
    srand(time(NULL));
    int n = 1000;
    int interval = 100;
    int flag = 0;
    times_r t1 = { 1, 5 };
    times_r t2 = { 0, 3 };
    times_r t3 = { 0, 4 };
    times_r t4 = { 0, 1 };

    int num_command = -1;

    while (num_command != 0)
    {
        print_hello();

        if (check_number(&num_command, 0, 4) != OK)
        {

            printf("%s" " %s",
                   "Error!!!",
                   "Incorrect command entered, try again!!!\n");

            break;
        }
        else
        {
            fflush (stdin);
            switch (num_command)
            {
                case 1:
                    printf(
                           "Simulation for an array queue.\n"
                           );
                    sd_array(n, interval, t1, t2, t3, t4);

                    break;
                case 2:
                    printf(
                           "Simulation for a queue in the form of a list.\n"
                           );
                    printf("Output memory information? \n1 - Yes, 0 - No\nChoice: ");
                    int rc = scanf("%d", &flag);
                    if (rc != 1 || !(flag == 1 || flag == 0))
                    {
                        printf("%s" " %s",
                               "Error!!!",
                               "Incorrect number entered!\n");
                        break;
                    }

                    sd_list(n, interval, t1, t2, t3, t4, flag);

                    break;
                case 3:
                    printf(
                           "Changing the processing time.\n"
                           );
                    double l, r;
                    int c;
                    printf("1: min = %lf; max = %lf\n", t1.min, t1.max);
                    printf("2: min = %lf; max = %lf\n", t2.min, t2.max);
                    printf("3: min = %lf; max = %lf\n", t3.min, t3.max);
                    printf("4: min = %lf; max = %lf\n", t4.min, t4.max);
                    printf("Which interval should I change?\n");
                    if (check_number(&c, 1, 4) != OK)
                    {

                        printf("%s" " %s",
                               "Error!!!",
                               "Incorrect number entered!\n");
                        break;
                    }
                    else
                    {
                        printf("Enter the left and right borders: ");
                        int rc = scanf("%lf", &l);
                        if (rc != 1)
                        {
                            printf("%s" " %s",
                                   "Error!!!",
                                   "Incorrect number entered!\n");
                            break;
                        }
                        rc = scanf("%lf", &r);
                        if (rc != 1)
                        {
                            printf("%s" " %s",
                                   "Error!!!",
                                   "Incorrect number entered!\n");
                            break;
                        }
                        if (c == 1)
                        {
                            t1.min = l;
                            t1.max = r;
                        }
                        if (c == 2)
                        {
                            t2.min = l;
                            t2.max = r;
                        }
                        if (c == 3)
                        {
                            t3.min = l;
                            t3.max = r;
                        }
                        if (c == 4)
                        {
                            t4.min = l;
                            t4.max = r;
                        }
                        printf("After\n");
                        printf("1: min = %lf; max = %lf\n", t1.min, t1.max);
                        printf("2: min = %lf; max = %lf\n", t2.min, t2.max);
                        printf("3: min = %lf; max = %lf\n", t3.min, t3.max);
                        printf("4: min = %lf; max = %lf\n", t4.min, t4.max);
                    }
                    break;
                case 4:
                    printf(
                           "Output of time comparisons\n"
                           );
                    memory_io();
                    break;
            }
        }
    }
    return OK;
}
