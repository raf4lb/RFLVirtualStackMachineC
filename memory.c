#include "memory.h"
#include <stdlib.h>
#include "serial.h"

Memory *create_memory(int size)
{
    Memory *memory = (Memory *)malloc(sizeof(Memory));
    if (memory == NULL)
    {
        serial_printf("Memory allocation failed for memory\n");
        exit(1);
    }
    memory->size = size;
    memory->data = (long int *)malloc(size * sizeof(long int));
    if (memory->data == NULL)
    {
        serial_printf("Memory allocation failed for memory data.\n");
        exit(1);
    }
    for (int i = 0; i < size; i++)
    {
        memory->data[i] = 0;
    }
    return memory;
}

void destroy_memory(Memory *mem) { free(mem->data); }