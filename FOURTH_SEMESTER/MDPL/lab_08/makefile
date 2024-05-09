_MAKE_OUT_DIR_ := $(shell mkdir -p out)
_MAKE_ASM_DIR_ := $(shell mkdir -p assembly)
_MAKE_DISASM_DIR_ := $(shell mkdir -p disassembly)

.PHONY: math_2 math_1 math_asm math pi run assembly disassembly clean

math_1:
	g++ compare.cpp -m80387 -O0 -o test_math_1.exe
	./test_math_1.exe
math_2:
	g++ compare.cpp -mno-80387 -O0 -o test_math_2.exe
	./test_math_2.exe
math_asm:
	g++ compare.cpp -masm=intel -DASM -O0 -o test_math_asm.exe
	./test_math_asm.exe

math: math_2 math_1 math_asm

pi:
	g++ pi.cpp -masm=intel -o 2.exe -lm
	./2.exe

solve:
	g++ task.cpp -masm=intel -c -o 3.o -lm
	g++ 3.o -o 3.exe
	./3.exe

ss:
	nasm -f win64 bi.asm -o bi.o
	g++ 3.o bi.o -o 3.exe

run: math pi

# Посмотреть ассемблерный код можно 2 способами:
assembly:
	g++ -S compare.cpp -mno-80387 -O0 -o assembly/test_math_2.s
	g++ -S compare.cpp -m80387 -O0 -o assembly/test_math_1.s
	g++ -S compare.cpp -masm=intel -DASM -O0 -o assembly/test_math_asm.s
	g++ -S pi.cpp -masm=intel -o assembly/2.s

disassembly:
	g++ -c compare.cpp -mno-80387 -O0 -o out/test_math_2.o
	g++ -c compare.cpp -m80387 -O0 -o out/test_math_1.o
	g++ -c compare.cpp -masm=intel -DASM -O0 -o out/test_math_asm.o
	g++ -c pi.cpp -masm=intel -o out/2.o
	objdump -M intel-mnemonic -d out/test_math_2.o  > disassembly/test_math_2.txt
	objdump -M intel-mnemonic -d out/test_math_1.o  > disassembly/test_math_1.txt
	objdump -M intel-mnemonic -d out/test_math_asm.o  > disassembly/test_math_asm.txt
	objdump -M intel-mnemonic -d out/2.o  > disassembly/2.txt

clean:
	rm -rf out/* assembly/* disassembly/* *.exe *.o