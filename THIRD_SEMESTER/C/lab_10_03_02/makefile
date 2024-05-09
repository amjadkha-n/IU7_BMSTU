CC := gcc
CFLAGS := -std=gnu99 -Iinc -Wall -Wpedantic -Wextra -g3
UNIT_OBJS := out/check_func_1.o out/check_main.o
OBJS := out/associative_array_impl_1.o
UNIT_L := -lcheck -lm
.PHONY : clean debug debug_asan debug_msan debug_ubsan unit my_unit func_tests
#$@ - имя цели
#$^ - список зависисомтей
#$< - первая зависимость
out/%.o : %.c *.h
	mkdir -p out
	$(CC) $(CFLAGS) -c $< -o $@
unit_tests.exe: out/associative_array_impl_2.o $(UNIT_OBJS)
	$(CC) -o $@ $^ $(UNIT_L)
unit : unit_tests.exe
	./unit_tests.exe

my_unit : UNIT_L += -lpthread -lrt -lsubunit
my_unit : unit_tests.exe
	./unit_tests.exe

clean:
	rm -f ./*.exe ./*.gcov ./out/*.o ./out/out.txt