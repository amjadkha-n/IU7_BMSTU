CFLAGS := -std=c99 -Wall -Werror -pedantic
UNIT_FLAGS := -lcheck -lm
TEST_OBJ := out/check_main.o 

app.exe : out/main.o out/func.o out/work_with_list.o 
	gcc -g -o app.exe out/main.o out/func.o out/work_with_list.o -lm

unit_tests.exe : out/func.o out/work_with_list.o $(TEST_OBJ)
	gcc -o unit_tests.exe out/func.o out/work_with_list.o $(TEST_OBJ) $(UNIT_FLAGS)

out/main.o : src/main.c
	gcc $(CFLAGS) -c -o out/main.o src/main.c

out/func.o : src/func.c inc/main.h
	gcc $(CFLAGS) -c -o out/func.o src/func.c

out/work_with_list.o : src/work_with_list.c inc/main.h
	gcc $(CFLAGS) -c -o out/work_with_list.o src/work_with_list.c

out/check_main.o : unit_tests/check_main.c inc/check_main.h
	gcc $(CFLAGS) -c -o out/check_main.o unit_tests/check_main.c


.PHONY : clean
.PHONY : func
.PHONY : my_unit

clean :
	$(RM) out/*.o *.exe

func : 
	cd ./func_tests && bash func.sh

my_unit : out/func.o out/work_with_list.o $(TEST_OBJ)
	gcc -o unit_tests.exe out/func.o out/work_with_list.o $(TEST_OBJ) $(UNIT_FLAGS) -lsubunit
