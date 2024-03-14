typedef struct {
  int size;
  int *data;
} Memory;

Memory create_memory(int size);

void destroy_memory(Memory *mem);