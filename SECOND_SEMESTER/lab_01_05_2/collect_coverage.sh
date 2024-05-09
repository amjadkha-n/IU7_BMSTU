#!/bin/bash

# Build the application with coverage flags
gcc -c main.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -O0 -g3 -fprofile-arcs -ftest-coverage
gcc main.o -o app.exe -lm -fprofile-arcs -ftest-coverage

# Run functional tests and generate coverage report
for file_name in func_tests/data/???_??_in.txt; do
	./app.exe < "$file_name" > out.txt 2>&1
done

# Print the coverage percentage
echo "Coverage: $(gcov main.c | grep -oE -m 1 '[0-9]+\.[0-9]+%')"

# Clean up generated files
rm -f main.o app.exe out.txt ./*.gcno ./*.gcda


