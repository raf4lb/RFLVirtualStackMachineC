#include "processor.h"
#include <stdlib.h>
#include <string.h>
#include "serial.h"

#ifndef PROGRAM
#define PROGRAM "{}"
#endif

#ifndef PROGRAM_SIZE
#define PROGRAM_SIZE 0
#endif

long int *convert_str_to_long_int(char str[], int size)
{
    long *array = malloc(size * sizeof(long)); // Dynamically allocate memory for the array

    // Check if memory allocation is successful
    if (array == NULL)
    {
        serial_printf("Memory allocation failed.\n");
        exit(1);
    }

    // Remove curly braces and split the string into individual elements
    char *token = strtok(str, "{,}");
    int i = 0;

    // Convert each element to long integer
    while (token != NULL)
    {
        array[i++] = strtol(token, NULL, 10);
        token = strtok(NULL, "{,}");
    }

    return array;
}

int main_processor()
{
    char program_string[] = PROGRAM;
    int program_size = PROGRAM_SIZE;
    long int *program = convert_str_to_long_int(program_string, program_size);

    int memory_size = 32;
    int stack_size = 32;
    int total_ports = 4;
    serial_setup();
    serial_printf("starting vm\n");
    Processor *processor = processor_create(memory_size, stack_size, total_ports);
    processor_run(processor, program, program_size, false);
    free(program);
    processor_free(processor);
    serial_printf("ending vm\n");
    return 0;
}

int main() { return main_processor(); }