# include "my_mod.h"
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return ARGS_ERROR;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        fprintf(stderr, "Failed to open the file: %s\n", argv[1]);
        return FILE_ERROR;
    }
    fseek(f, 0, SEEK_END);
    if (ftell(f) == 0)
    {
        printf("The input file is empty.\n");
        fclose(f);
        return NO_NUMBER;
    }
    fseek(f, 0, SEEK_SET);
    
    int error;
    double avg = 0;
    error = count_average(f, &avg);
    if (error != EXIT_SUCCESS)
    {
        fclose(f);
        return error;
    }

    rewind(f);

    double disp = 0;
    error = count_variance(f, avg, &disp);
    if (error != EXIT_SUCCESS)
    {
        fclose(f);
        return error;
    }

    fclose(f);

    fprintf(stdout, "Variance: %lf\n", disp);

    return EXIT_SUCCESS;
}
