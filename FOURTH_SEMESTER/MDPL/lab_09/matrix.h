# include <iostream>
# include <stdio.h>
# define OK 0
# define ERROR 1
struct matrix_t
{
    double **data;
    int m;
    int n;
};
matrix_t memory_alloc(int m, int n);
void memory_free(matrix_t &matrix);
void read_size(int &m, int &n);
void read_matrix(matrix_t &matrix, int rows, int columns);
void print_matrix(matrix_t &matrix);
static double multiply_and_add_SSE(double *sa, double *sb, int n);
matrix_t matrix_multiply_SSE(matrix_t &a, matrix_t &b);
matrix_t matrix_multiply_CPP(matrix_t &a, matrix_t &b);

