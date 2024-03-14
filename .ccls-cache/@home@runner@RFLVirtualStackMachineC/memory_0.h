#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int size;
  int *data;
} Memory;

typedef struct {
  Memory memory;
  int sp;
} Stack;

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

Stack create_stack(int size) {
  Stack stack;
  stack.memory = create_memory(size);
  stack.sp = 0;
  return stack;
}

void push(Stack *stack, int value) {
  stack->memory.data[stack->sp] = value;
  stack->sp++;
}

int pop(Stack *stack) {
  stack->sp--;
  return stack->memory.data[stack->sp];
}

void pprint(Stack *stack) {
  printf("[");
  for (int i = 0; i < stack->memory.size; i++) {
    if (i > 0)
      printf(", ");
    if (i == stack->sp - 1)
      printf("->%d", stack->memory.data[i]);
    else
      printf("%d", stack->memory.data[i]);
  }
  printf("]\n");
}

int get_top(Stack *stack) { return stack->memory.data[stack->sp - 1]; }
