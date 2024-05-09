#!/bin/bash

gcc -c main.c my_string.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -O0 -g3 -fprofile-arcs -ftest-coverage -fsanitize=address
gcc main.o my_string.o -o main -lm -fprofile-arcs -ftest-coverage -fsanitize=address

