#include "memory.h"

typedef struct
{
    Memory *memory;
    int sp;
} Stack;

void stack_push(Stack *stack, int value);

int stack_pop(Stack *stack);

int stack_get_top(Stack *stack);

void stack_pprint(Stack *stack);

Stack *create_stack(int size);

void stack_free(Stack *stack);