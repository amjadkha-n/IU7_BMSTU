CC = aarch64-linux-gnu-g++
QEMU = qemu-aarch64
TARGET = my_program
SOURCE = main.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
		$(CC) $^ -o $@

run: $(TARGET)
		$(QEMU) -L /usr/aarch64-linux-gnu ./$< 

clean:
		rm -f $(TARGET)