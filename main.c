#include "ALU.h"
#include "processor.h"
#include <stdio.h>
#include <stdlib.h>

int main_stack() {
  Stack stack = create_stack(10);

  stack_push(&stack, 5);
  stack_push(&stack, 10);
  stack_push(&stack, 15);

  stack_pprint(&stack);

  int top = stack_get_top(&stack);
  printf("Top element: %d\n", top);

  int popped = stack_pop(&stack);
  printf("Popped element: %d\n", popped);

  stack_pprint(&stack);

  destroy_memory(&stack.memory);

  return 0;
}

int main_alu() {
  ALU alu = create_alu();
  // Example usage
  int result_add = alu.add(5, 3);
  int result_subtract = alu.subtract(5, 3);
  int result_multiply = alu.multiply(5, 3);
  int result_divide = alu.divide(5, 3);
  int result_logic_and = alu.logic_and(1, 0);

  printf("Addition: %d\n", result_add);
  printf("Subtraction: %d\n", result_subtract);
  printf("Multiplication: %d\n", result_multiply);
  printf("Division: %d\n", result_divide);
  printf("Logical AND: %d\n", result_logic_and);

  return 0;
}

int main_isa() {
  Instruction *isa = create_ISA();
  for (int i = 0; i < 18; i++) {
    printf("%s: %d\n", isa[i].name, isa[i].opcode);
  }
  return 0;
}

int main_processor() {
  Processor *processor = create_processor(32, 32);
  // blink led
  // int program[9] = {131073, 393216, 196608, 328680, 131072,
  //                 393216, 328680, 196608, 262144};

  // for
  const int program_size = 13;
  int program[program_size] = {131072, 196608, 131082, 196609, 131073,
                               196610, 65536,  393216, 65538,  458752,
                               786433, 0,      262151};
  // inc_dec
  // const int program_size = 19;
  // int program[program_size] = {131072, 196608, 131082, 196609, 131072,
  //                              393216, 262151, 131073, 458752, 393216,
  //                              983041, 262151, 262157, 131073, 524288,
  //                              393216, 917504, 262157, 0};

  run(processor, program, program_size, false);
  return 0;
}

int main() { return main_processor(); }
