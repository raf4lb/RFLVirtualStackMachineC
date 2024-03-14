#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

Memory create_memory(int size) {
  Memory mem;
  mem.size = size;
  mem.data = (int *)malloc(size * sizeof(int));
  if (mem.data == NULL) {
    printf("Memory allocation failed.\n");
    exit(1);
  }
  for (int i = 0; i < size; i++) {
    mem.data[i] = 0;
  }
  return mem;
}

void destroy_memory(Memory *mem) { free(mem->data); }