#include "matrix.h"

matrix_t memory_alloc(int m, int n)
{
    matrix_t matrix;
    matrix.m = m;
    matrix.n = n;

    matrix.data = (double**)calloc(matrix.m, sizeof(double*));
    for (int i = 0; i < matrix.m; i++)
    {
        matrix.data[i] = (double*)calloc(matrix.n + matrix.n % 2, sizeof (double));
    }
    return matrix;
}

void memory_free(matrix_t &matrix)
{
    for (int i = 0; i < matrix.m; i++)
    {
        if (matrix.data[i])
        {
            free(matrix.data[i]);
        }
        matrix.data[i] = NULL;
    }
    if (matrix.data)
    {
        free(matrix.data);
    }
    matrix.data = NULL;
    matrix.m = 0;
    matrix.n = 0;
}

void read_size(int &m, int &n)
{
    std::cout << "Please enter the number of rows: "; 
    std::cin >> m;
    std::cout << "Please enter the number of columns: ";
    std::cin >> n;
}

void read_matrix(matrix_t &matrix, int rows, int columns)
{
    std::cout << "Please enter the elements of the matrix: " << std::endl;
    matrix = memory_alloc(rows, columns);

    for (int i = 0; i < matrix.m; i++)
    {
        for (int j = 0; j < matrix.n; j++)
        {
            std::cin >> matrix.data[i][j];
        }
    }
}

void print_matrix(matrix_t &matrix)
{
    for (int i = 0; i < matrix.m; i++)
    {
        for (int j = 0; j < matrix.n; j++)
        {
            std::cout << matrix.data[i][j] << "\t";
        }
        std::cout << std::endl;

    }
}

matrix_t matrix_transpose(matrix_t &matrix)
{
    matrix_t res = memory_alloc(matrix.n, matrix.m);

    for (int i = 0; i < matrix.n; i++)
    {
        for (int j = 0; j < matrix.m; j++)
        {
            res.data[j][i] = matrix.data[i][j];
        }
    }
    return res;
}

static double multiply_and_add_standard(double *a, double *b, int n)
{
    double temp = 0;
    for (int i = 0; i < n; i++)
    {
        temp += a[i] * b[i];
    }
    return temp;
}
// The 128-bit XMM registers are part of the SSE extension (where SSE is short for Streaming SIMD Extension, and SIMD, in turn, stands for 
// single instruction multiple data). There are eight XMM registers available in non -64-bit modes and 16 XMM registers in long mode, which 
// allow simultaneous operations on: 16 bytes.
// This function multiplies two arrays of doubles using SSE (Streaming SIMD Extensions) instructions and adds the results.1
static double multiply_and_add_SSE(double *sa, double *sb, int m)
{
    double temp = 0.0; // Initialize a temporary variable to store the partial result.
    double res = 0.0; // Initialize a variable to store the final result.
    // __float128 is a data type in C and C++ that can store very large or very small decimal numbers with high precision. It is 128 bits in size, 
    // which allows it to represent numbers with more decimal places than the standard double data type.
    __float128 *a = (__float128 *)sa; // Cast the input array 'sa' to an array of __float128 to align memory for SSE instructions.
    __float128 *b = (__float128 *)sb; // Cast the input array 'sb' to an array of __float128 to align memory for SSE instructions.

    // Iterate over the arrays in steps of the size of __float128 in doubles.
    // The size of __float128 in C++ is typically 16 bytes (128 bits). It is a data type that provides extended precision floating-point arithmetic.
    // the size of __float128 is typically 16 bytes (128 bits) and the size of double is 8 bytes (128 bits).So in the following loop i will increment
    // each time +2.
    for (size_t i = 0; i < m; i += sizeof(__float128) / sizeof(double), a++, b++)
    
    {
        // Inline assembly block to execute SSE instructions.
        __asm__
        (
            // movapd is an instruction used to move a double-precision floating-point value from one location to another. It is specifically 
            // used for moving data between two 128-bit XMM registers.
            // Move the contents of array 'a' to XMM0 register.
            // extended memeory manager (xmm)
            "movapd xmm0, %1\n"
            // Move the contents of array 'b' to XMM1 register.
            "movapd xmm1, %2\n"
            // MULPD — Multiply Packed Double Precision Floating-Point Values.
            // In assembly language, mulpd is an instruction used to multiply packed double-precision floating-point values. 
            // Multiply packed double-precision floating-point values in XMM0 with packed double-precision floating-point values in XMM1.
            "mulpd xmm0, xmm1\n"
            // HADDPD — Packed Double Precision Floating-Point Horizontal Add.
            // Horizontally add the packed double-precision floating-point values in XMM0.
            "haddpd xmm0, xmm0\n"
            // Move the lower double-precision floating-point value from XMM0 to 'temp'.
            "movsd %0, xmm0\n"
            // Output operands.
            : "=m" (temp) // Output operand: 'temp'
            // Input operands.
            : "m" (*a), "m" (*b) // Input operands: arrays 'a' and 'b'
            // Clobbers: specify which registers are modified by the assembly code.
            : "xmm0", "xmm1" // Clobbered registers: XMM0 and XMM1
        );
        // Accumulate the partial result to the final result.
        res += temp;
    }
    // Return the final result.
    return res;
}


matrix_t matrix_multiply_SSE(matrix_t &a, matrix_t &b)
{
    matrix_t transpose_b = matrix_transpose(b);
    matrix_t res = memory_alloc(a.m, b.m);

    for (int i = 0; i < res.m; i++)
    {
        for (int j = 0; j < res.n; j++)
        {
            res.data[i][j] = multiply_and_add_SSE(a.data[i], transpose_b.data[j], a.m);
        }
    }
    memory_free(transpose_b);
    return res;
}


matrix_t matrix_multiply_CPP(matrix_t &a, matrix_t &b)
{
    matrix_t transpose_b = matrix_transpose(b);
    matrix_t res = memory_alloc(a.m, b.m);
    {
        for (int i = 0; i < res.m; i++)
        {
            for (int j = 0; j < res.n; j++)
            {
                res.data[i][j]  = multiply_and_add_standard(a.data[i], transpose_b.data[j], a.m);
            }
        }
    }
    memory_free(transpose_b);
    return res;
}
