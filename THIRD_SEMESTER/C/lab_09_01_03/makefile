CFLAGS := -std=c99 -Wall -Werror -pedantic
UNIT_FLAGS := -lcheck -lm
TEST_OBJ := out/check_main.o 

app.exe : out/main.o out/my_mod.o
	gcc -g -o app.exe out/main.o out/my_mod.o

unit_tests.exe : out/my_mod.o $(TEST_OBJ)
	gcc -o unit_tests.exe out/my_mod.o $(TEST_OBJ) $(UNIT_FLAGS)

out/main.o : src/main.c
	gcc $(CFLAGS) -c -o out/main.o src/main.c

out/my_mod.o : src/my_mod.c inc/my_mod.h
	gcc $(CFLAGS) -c -o out/my_mod.o src/my_mod.c

out/check_main.o : unit_tests/check_main.c inc/check_main.h
	gcc $(CFLAGS) -c -o out/check_main.o unit_tests/check_main.c


.PHONY : clean
.PHONY : func
.PHONY : my_unit

clean :
	$(RM) out/*.o *.exe

func : 
	cd ./func_tests && bash func.sh

my_unit : out/my_mod.o $(TEST_OBJ)
	gcc -o unit_tests.exe out/my_mod.o $(TEST_OBJ) $(UNIT_FLAGS) -lsubunit -lcheck -lm -lrt -lpthread
