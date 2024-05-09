# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <ctype.h>

# define EXIT_SUCCESS 0
# define COUNT_READ 1
# define ARGS_ERROR 1
# define FILE_ERROR 2
# define NO_NUMBER 3
# define ONE_NUMBER 4

int count_average(FILE *f, double *avg);
int count_variance(FILE *f, double avg, double *disp);
