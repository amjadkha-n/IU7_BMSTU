#!/bin/bash

clang -c main.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -O0 -g3 -fsanitize=address,undefined -fprofile-arcs -ftest-coverage
clang main.o -o app.exe -lm -fsanitize=address,undefined -fprofile-arcs -ftest-coverage

