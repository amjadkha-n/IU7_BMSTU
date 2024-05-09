CC := gcc

CFLAGS := -std=gnu99 -Wall -Werror -pedantic -ggdb -I inc

OBJS_MAIN := out/film_in_out.o out/f_process.o out/process.o

OBJS_UNITS := out/check_binary_search.o out/process.o out/film_in_out.o

app.exe : out/main.o $(OBJS_MAIN)
	$(CC) -o $@ $^

unit_tests.exe : out/check_main.o $(OBJS_UNITS)
	$(CC) -o $@ $^ -lcheck -lsubunit -lm


out/main.o : src/main.c
	mkdir -p out
	$(CC) $(CFLAGS) -c $^ -o $@

out/film_in_out.o : src/film_in_out.c inc/film_in_out.h
	mkdir -p out
	$(CC) $(CFLAGS) -c src/film_in_out.c -o $@

out/f_process.o : src/f_process.c inc/f_process.h
	mkdir -p out
	$(CC) $(CFLAGS) -c src/f_process.c -o $@

out/process.o : src/process.c inc/process.h
	mkdir -p out
	$(CC) $(CFLAGS) -c src/process.c -o $@

out/check_main.o : unit_tests/check_main.c
	mkdir -p out
	$(CC) $(CFLAGS) -c $^ -lcheck -o $@

out/check_binary_search.o : unit_tests/check_binary_search.c inc/check_binary_search.h
	mkdir -p out
	$(CC) $(CFLAGS) -c unit_tests/check_binary_search.c -lcheck -o $@

.PHONY : clean
clean :
	rm out/*.o *.exe
