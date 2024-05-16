# include "matrix.h"
int main()
{
    matrix_t a, b;
    std::cout << "A Matrix: " << std::endl;
    read_size(a.m, a.n);
    if (a.m <= 0 || a.n <= 0)
    {
        std::cout << "Invalid input!" << std::endl;
        return ERROR;
    }
    // std::cout << "Please enter the elements of the first matrix: " << std::endl;
    read_matrix(a, a.m, a.n);
    std::cout << "\nB Matrix: " << std::endl;
    read_size(b.m, b.n);
    if (b.m <= 0 || b.n <= 0)
    {
        std::cout << "Invalid input! " << std::endl;
        memory_free(a);
        return ERROR;
    }
    // std::cout << "Please enter the elements of the second matrix: " << std::endl;
    read_matrix(b, b.m, b.m);

    std::cout << "\nFirst Matrix: " << std::endl;
    print_matrix(a);
    std::cout << "\nSecond matrix: " << std::endl;
    print_matrix(b);
    
    if (a.n != b.m)
    {
        std::cout << "Error: The number of columns of the first matrix must match the number of rows of the second matrix!" << std::endl;
        memory_free(a);
        memory_free(b);
        return ERROR;
    }
    else
    {
        std::cout << "\nSSE result: " << std::endl;
        matrix_t res_1 = matrix_multiply_SSE(a, b);
        print_matrix(res_1);
        memory_free(res_1);

        std::cout << "\nCPP result: " << std::endl;
        matrix_t res_2 = matrix_multiply_CPP(a, b);
        print_matrix(res_2);
        memory_free(res_2);
    }
    memory_free(a);
    memory_free(b);

    return 0;

}