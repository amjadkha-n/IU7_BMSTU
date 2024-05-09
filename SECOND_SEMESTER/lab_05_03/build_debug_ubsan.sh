#!/bin/bash

gcc -c main.c my_mod.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -O0 -g3 -fsanitize=undefined -fno-sanitize-recover=all
gcc main.o my_mod.o -o main -lm -fsanitize=undefined -fno-sanitize-recover=all

