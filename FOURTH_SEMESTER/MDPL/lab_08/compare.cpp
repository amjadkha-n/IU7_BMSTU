#include <stdio.h>
#include <iostream>
#include <time.h>
#include <chrono>

#define REPEAT_COUNTS 1e7
template <typename T>
void time_measurement_cpp(size_t times, T a, T b)
{
    T res;

    std::chrono::duration<double> time_sum(0);
    std::chrono::duration<double> time_mul(0);

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < times; i++)
    {
        res = a + b;
    }
    time_sum = std::chrono::high_resolution_clock::now() - start;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < times; i++)
    {
        res = a * b;
    }
    time_mul = std::chrono::high_resolution_clock::now() - start;

    std::cout << "Sum: " << time_sum.count() << "\tProduct: " << time_mul.count() << std::endl;
}

template <typename T>
void time_measurement_asm(size_t times, T a, T b)
{
    T res;

    std::chrono::duration<double> time_sum(0);
    std::chrono::duration<double> time_mul(0);
    
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < times; i++)
    {
        __asm__ 
        (
            "fld %1\n"
            "fld %2\n"

            "faddp\n"

            "fstp %0\n"

            : "=m" (res)
            : "m" (a), 
              "m" (b)
        );
    }
    time_sum = std::chrono::high_resolution_clock::now() - start;

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < times; i++)
    {
        __asm__ 
        (
            "fld %1\n"
            "fld %2\n"

            "fmulp\n"
            "fstp %0\n"
            
            : "=m" (res)
            : "m" (a),
              "m" (b)
        );
    }
    time_mul = std::chrono::high_resolution_clock::now() - start;

    std::cout << "Sum: " << time_sum.count() << "\tProduct: " << time_mul.count() << std::endl;
}

#ifdef ASM
#define TIME_MEASUREMENT(T) time_measurement_asm<T>
#else
#define TIME_MEASUREMENT(T) time_measurement_cpp<T>
#endif

#define OK 0

int main()
{
    double a = -1.1, b = 1234.5;
    printf("float:\n");
    TIME_MEASUREMENT(float)(REPEAT_COUNTS, a, b);
    printf("double:\n");
    TIME_MEASUREMENT(double)(REPEAT_COUNTS, a, b);
    return OK;
}