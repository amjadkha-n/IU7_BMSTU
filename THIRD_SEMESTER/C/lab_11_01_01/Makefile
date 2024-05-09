CFLAGS := -std=c99 -Wall -Werror -pedantic
UNIT_FLAGS := -lcheck -lm
TEST_OBJ := out/check_main.o 

app.exe : out/main.o out/my_snprintf.o
	gcc -g -o app.exe out/main.o out/my_snprintf.o -lm

unit_tests.exe : out/my_snprintf.o $(TEST_OBJ)
	gcc -o unit_tests.exe out/my_snprintf.o $(TEST_OBJ) $(UNIT_FLAGS)

out/main.o : src/main.c
	gcc $(CFLAGS) -g -c -o out/main.o src/main.c
	
out/my_snprintf.o : src/my_snprintf.c inc/my_snprintf.h
	gcc $(CFLAGS) -g -c -o out/my_snprintf.o src/my_snprintf.c

out/check_main.o : unit_tests/check_main.c inc/check_main.h
	gcc $(CFLAGS) -c -o out/check_main.o unit_tests/check_main.c


.PHONY : clean
.PHONY : func
.PHONY : my_unit

clean :
	$(RM) out/*.o *.exe

func : 
	cd ./func_tests && bash func.sh

my_unit : out/my_snprintf.o $(TEST_OBJ)
	gcc -o unit_tests.exe out/my_snprintf.o $(TEST_OBJ) $(UNIT_FLAGS) -lsubunit
