#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void stack_push(Stack *stack, int value) {
  stack->memory.data[stack->sp] = value;
  stack->sp++;
}

int stack_pop(Stack *stack) {
  stack->sp--;
  return stack->memory.data[stack->sp];
}

void stack_pprint(Stack *stack) {
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

int stack_get_top(Stack *stack) { return stack->memory.data[stack->sp - 1]; }

Stack create_stack(int size) {
  Stack stack;
  stack.memory = create_memory(size);
  stack.sp = 0;
  return stack;
}