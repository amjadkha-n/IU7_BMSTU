#!/bin/bash

gcc -c main.c my_mod.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -O3
gcc main.o my_mod.o -o main -lm

