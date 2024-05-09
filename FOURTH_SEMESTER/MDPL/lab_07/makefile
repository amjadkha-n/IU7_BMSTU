app.exe : main.o my_asm_copy.o my_string_len.o
	gcc $^ -o $@

main.o : main.c my_string_len.h
	gcc -c -ggdb $<

my_string_len.o : my_string_len.c my_string_len.h
	gcc -c -ggdb -masm=intel $<

my_asm_copy.o : my_asm_copy.asm
	nasm -f elf64 $<

clean:
	rm -rf *.o *.s