all: main

CC = clang
override CFLAGS += -g -Wno-everything -pthread -lm

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

main: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o build/"$@"

main-debug: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -O0 $(SRCS) -o build/"$@"

generic: $(SRCS) $(HEADERS)
	mkdir build
	$(CC) $(CFLAGS) $(SRCS) -o build/$@


arduino:
	mkdir build
	avr-gcc -Os -mmcu=atmega328p -c ALU.c -o build/ALU.o
	avr-gcc -Os -mmcu=atmega328p -c memory.c -o build/memory.o
	avr-gcc -Os -mmcu=atmega328p -c stack.c -o build/stack.o
	avr-gcc -Os -mmcu=atmega328p -c delay.c -o build/delay.o
	avr-gcc -Os -mmcu=atmega328p -c io.c -o build/io.o
	avr-gcc -Os -mmcu=atmega328p -c processor.c -o build/processor.o
	avr-gcc -Os -mmcu=atmega328p -c main.c -o build/main.o
	avr-gcc -Os -mmcu=atmega328p build/ALU.o build/memory.o build/stack.o build/delay.o build/io.o build/processor.o build/main.o -o build/main.bin
	avr-objcopy -O ihex -R .eeprom build/main.bin build/main.hex

clean:
	rm -f main main-debug
	rm -r build