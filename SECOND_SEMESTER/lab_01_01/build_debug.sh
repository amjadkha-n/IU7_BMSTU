#!/bin/bash

gcc -c main.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -O0 -g3 -fprofile-arcs -ftest-coverage
gcc main.o -o app.exe -lm -fprofile-arcs -ftest-coverage
