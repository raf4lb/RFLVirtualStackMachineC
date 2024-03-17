typedef struct
{
    int size;
    long int *data;
} Memory;

Memory *create_memory(int size);

void destroy_memory(Memory *memory);