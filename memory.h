typedef struct
{
    int size;
    long int *data;
} Memory;

Memory *create_memory(int size);

void memory_pprint(Memory *memory);

void memory_free(Memory *memory);