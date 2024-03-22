all: main

CC = clang
override CFLAGS += -g -Wno-everything -pthread -lm

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

BUILDDIR = build

generic:
	$(eval PYTHON_SCRIPT := compiler.py)
	@echo "Compiling rfl file..."
	$(eval OUTPUT := $(shell python3 $(PYTHON_SCRIPT) $(PROGRAM_FILE) $(PORTS_SIZE)))
	@echo "OK"
	$(eval PROGRAM := $(word 1, $(OUTPUT)))
	$(eval PROGRAM_SIZE := $(word 2, $(OUTPUT)))
	@echo "Program: $(PROGRAM)"
	@echo "Size: $(PROGRAM_SIZE)"
	mkdir -p $(BUILDDIR)
	@echo "Sending code to RFLVM"
	$(CC) $(SRCS) -DPROGRAM=\""$(PROGRAM)"\" -DPROGRAM_SIZE=$(PROGRAM_SIZE) -o build/$@

arduino:
	mkdir -p build
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
	