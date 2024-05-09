#!/bin/bash

clang -c main.c my_string.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -O0 -g3 -fsanitize=address,undefined -fprofile-arcs -ftest-coverage
clang main.o my_string.o -o main -lm -fsanitize=address,undefined -fprofile-arcs -ftest-coverage

