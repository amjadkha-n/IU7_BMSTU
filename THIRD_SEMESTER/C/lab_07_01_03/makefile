CFLAGS = -std=c99 -Wall -Werror -pedantic -Wfloat-conversion -Wvla -Wfloat-equal -Wpedantic -Wextra -Iinc -g3
CC = gcc
RESULTS = 0
.PHONY: clean

app.exe: out/app.o out/functions.o out/arguments.o
	$(CC) -o $@ $^

out/app.o: src/main.c inc/check_main.h
	$(CC) $(CFLAGS) -c $< -o $@

out/functions.o: src/functions.c inc/check_main.h
	$(CC) $(CFLAGS) -c $< -o $@

out/arguments.o: src/arguments.c inc/check_main.h
	$(CC) $(CFLAGS) -c $< -o $@

unit_tests.exe: out/unit_tests.o out/check_key.o out/check_mysort.o out/functions.o
	$(CC) -o $@ $^

out/unit_tests.o: unit_tests/unit_main.c inc/check_key.h inc/check_mysort.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_key.o: unit_tests/check_key.c inc/check_main.h
	$(CC) $(CFLAGS) -c $< -o $@

out/check_mysort.o: unit_tests/check_mysort.c inc/check_main.h
	$(CC) $(CFLAGS) -c $< -o $@

timer.exe: out/timer.o out/functions.o
	$(CC) -o $@ $^

out/timer.o: unit_tests/timer.c inc/check_main.h
	$(CC) $(CFLAGS) -c $< -o $@

unit:
	./unit_tests.exe

func: test.sh
	./test.sh

clean:
	rm out/*.o
