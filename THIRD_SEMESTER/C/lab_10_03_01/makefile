CC := gcc
O := out/associative_array_impl_1.o
FLAGS := -std=gnu99 -Iinc -Wall -Wpedantic -Wextra
UNIT_O := out/check_func_1.o out/check_main.o

UNIT_F := -lm -lcheck

out/%.o : %.c *.h
	mkdir -p out
	$(CC) $(FLAGS) -c $< -o $@

unit_tests.exe : $(O) $(UNIT_O)
	$(CC) -o $@ $^ $(UNIT_F)

Debug : FLAGS += -g3
Debug : app.exe


unit : unit_tests.exe
	./unit_tests.exe

clean:
	rm -f ./*.exe ./*.gcov ./out/*.o ./out/out.txt 