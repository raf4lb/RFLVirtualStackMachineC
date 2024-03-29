#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

Memory *create_memory(int size)
{
    Memory *memory = (Memory *)malloc(sizeof(Memory));
    if (memory == NULL)
    {
        fprintf(stderr, "Memory allocation failed for memory\n");
        exit(1);
    }
    memory->size = size;
    memory->data = (long int *)malloc(size * sizeof(long int));
    if (memory->data == NULL)
    {
        printf("Memory allocation failed for memory data.\n");
        exit(1);
    }
    for (int i = 0; i < size; i++)
    {
        memory->data[i] = 0;
    }
    return memory;
}

void memory_pprint(Memory *memory){
    printf("[");
    for (int i = 0; i < memory->size; i++)
    {
        if (i > 0)
            printf(", ");
        printf("%ld", memory->data[i]);
    }
    printf("]\n");
}

void memory_free(Memory *memory) { 
    free(memory->data);
    free(memory);
}