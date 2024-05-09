CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic -Wfloat-conversion -Wvla -Wfloat-equal -Wpedantic -Wextra -Iinc -g3
.PHONY = clean

app.exe: out/main.o out/matrix_in_out.o out/operations.o
	$(CC) -o $@ $^ -lm

out/main.o: src/main.c inc/constants.h inc/matrix.h inc/matrix_in_out.h inc/operations.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/matrix_in_out.o: src/matrix_in_out.c inc/matrix_in_out.h inc/constants.h inc/matrix.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/operations.o: src/operations.c inc/matrix.h inc/constants.h inc/matrix_in_out.h
	$(CC) $(CFLAGS) -o $@ -c $<

unit_tests.exe: out/test_main.o out/test_operations.o out/operations.o out/matrix_in_out.o
	$(CC) -o $@ $^ -lm

out/test_main.o: unit_tests/test_main.c inc/test_operations.h
	$(CC) $(CFLAGS) -o $@ -c $<

out/test_operations.o: unit_tests/test_operations.c inc/operations.h inc/matrix.h
	$(CC) $(CFLAGS) -o $@ -c $<

unit: unit_tests.exe
	./unit_tests.exe

clean:
	rm out/*.o log/*
