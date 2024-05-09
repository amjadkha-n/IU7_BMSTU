#!/bin/bash

gcc -c main.c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -O0 -g3 -fprofile-arcs -ftest-coverage -lm
#!/bin/bash

#gcc -std=c99 -fprofile-arcs -ftest-coverage -Wall -Wextra -pedantic -O0 -g main.c -o main -lm
gcc main.o -o app.exe -lm -fprofile-arcs -ftest-coverage
