#include "stack.h"
#include <stdlib.h>
#include "serial.h"

void stack_push(Stack *stack, int value)
{
    if (stack->sp == stack->memory->size)
    {
        serial_printf("ERROR: STACKOVERFLOW");
        exit(1);
    }
    stack->memory->data[stack->sp] = value;
    stack->sp++;
}

int stack_pop(Stack *stack)
{
    if (stack->sp == 0)
    {
        serial_printf("ERROR: STACKUNDERFLOW");
        exit(1);
    }
    stack->sp--;
    return stack->memory->data[stack->sp];
}

void stack_pprint(Stack *stack)
{
    serial_printf("[");
    for (int i = 0; i < stack->memory->size; i++)
    {
        if (i > 0)
            serial_printf(", ");
        if (i == stack->sp - 1)
            serial_printf("->%ld", stack->memory->data[i]);
        else
            serial_printf("%ld", stack->memory->data[i]);
    }
    serial_printf("]\n");
}

long int stack_get_top(Stack *stack) { return stack->memory->data[stack->sp - 1]; }

Stack *create_stack(int size)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL)
    {
        serial_printf("Memory allocation failed for stack\n");
        exit(1);
    }
    stack->memory = create_memory(size);
    stack->sp = 0;
    return stack;
}

void stack_free(Stack *stack)
{
    memory_free(stack->memory);
    free(stack);
}