#include "processor.h"
#include "ALU.h"
#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define F_CPU 16000000UL
#include <util/delay.h> // Delay functions

int OPCODE_HALT = 0;
int OPCODE_PUSH = 1;
int OPCODE_PUSH_LITERAL = 2;
int OPCODE_POP = 3;
int OPCODE_DELAY = 4;
int OPCODE_TOP = 5;
int OPCODE_ADD = 6;
int OPCODE_SUBTRACT = 7;
int OPCODE_MULTIPLY = 8;
int OPCODE_DIVIDE = 9;
int OPCODE_JUMP = 10;
int OPCODE_JUMP_EQUAL = 11;
int OPCODE_JUMP_LESS = 12;
int OPCODE_JUMP_GREATER = 13;
int OPCODE_JUMP_LESS_EQUAL = 14;
int OPCODE_JUMP_GREATER_EQUAL = 15;
int OPCODE_CALL = 16;
int OPCODE_RET = 17;
char *NAME_HALT = "HLT";
char *NAME_PUSH = "PSH";
char *NAME_PUSH_LITERAL = "PSHL";
char *NAME_POP = "POP";
char *NAME_DELAY = "DLY";
char *NAME_TOP = "TOP";
char *NAME_ADD = "ADD";
char *NAME_SUBTRACT = "SUB";
char *NAME_MULTIPLY = "MUL";
char *NAME_DIVIDE = "DIV";
char *NAME_JUMP = "JMP";
char *NAME_JUMP_EQUAL = "JE";
char *NAME_JUMP_LESS = "JL";
char *NAME_JUMP_GREATER = "JG";
char *NAME_JUMP_LESS_EQUAL = "JLE";
char *NAME_JUMP_GREATER_EQUAL = "JGE";
char *NAME_CALL = "CALL";
char *NAME_RET = "RET";

void HaltInstruction_execute(Processor *processor, int operand) { exit(0); }

void PushInstruction_execute(Processor *processor, int address) {
  stack_push(processor->stack, processor_get_address(processor, address));
}

void PushLiteralInstruction_execute(Processor *processor, int value) {
  stack_push(processor->stack, value);
}

void PopInstruction_execute(Processor *processor, int address) {
  int value = stack_pop(processor->stack);
  processor_set_address(processor, address, value);
}

void blink_led() {}

void DelayInstruction_execute(Processor *processor, int value) {
  DDRB = DDRB | (1 << DDB5);
  PORTB = PORTB | (1 << PORTB5);
  _delay_ms(1000);
  PORTB = PORTB & ~(1 << PORTB5);
  _delay_ms(1000);
}

void TopInstruction_execute(Processor *processor, int operand) {
  printf("%d\n", stack_get_top(processor->stack));
}

void AddInstruction_execute(Processor *processor, int operand) {
  int b = stack_pop(processor->stack);
  int a = stack_pop(processor->stack);
  stack_push(processor->stack, add(a, b));
}

void SubtractInstruction_execute(Processor *processor, int operand) {
  int b = stack_pop(processor->stack);
  int a = stack_pop(processor->stack);
  stack_push(processor->stack, subtract(a, b));
}

void MultiplyInstruction_execute(Processor *processor, int operand) {
  int b = stack_pop(processor->stack);
  int a = stack_pop(processor->stack);
  stack_push(processor->stack, multiply(a, b));
}

void DivideInstruction_execute(Processor *processor, int operand) {
  int b = stack_pop(processor->stack);
  int a = stack_pop(processor->stack);
  stack_push(processor->stack, divide(a, b));
}

void JumpInstruction_execute(Processor *processor, int address) {
  processor->pc = address;
}

void JumpEqualInstruction_execute(Processor *processor, int address) {
  if (stack_get_top(processor->stack) ==
      processor_get_address(processor, address)) {
    processor->pc++;
  }
}

void JumpLessInstruction_execute(Processor *processor, int address) {
  if (stack_get_top(processor->stack) <
      processor_get_address(processor, address)) {
    processor->pc++;
  }
}

void JumpGreaterInstruction_execute(Processor *processor, int address) {
  if (stack_get_top(processor->stack) >
      processor_get_address(processor, address)) {
    processor->pc++;
  }
}

void JumpLessEqualInstruction_execute(Processor *processor, int address) {
  if (stack_get_top(processor->stack) <=
      processor_get_address(processor, address)) {
    processor->pc++;
  }
}

void JumpGreaterEqualInstruction_execute(Processor *processor, int address) {
  if (stack_get_top(processor->stack) >=
      processor_get_address(processor, address)) {
    processor->pc++;
  }
}

void CallInstruction_execute(Processor *processor, int address) {
  stack_push(processor->call_stack, processor->pc);
  processor->pc = address;
}

void ReturnInstruction_execute(Processor *processor, int operand) {
  int address = stack_pop(processor->call_stack);
  processor->pc = address;
}

Instruction create_HaltInstruction() {
  Instruction instruction;
  instruction.name = NAME_HALT;
  instruction.opcode = OPCODE_HALT;
  instruction.execute = HaltInstruction_execute;
  return instruction;
}

Instruction create_PushInstruction() {
  Instruction instruction;
  instruction.name = NAME_PUSH;
  instruction.opcode = OPCODE_PUSH;
  instruction.execute = PushInstruction_execute;
  return instruction;
}

Instruction create_PushLiteralInstruction() {
  Instruction instruction;
  instruction.name = NAME_PUSH_LITERAL;
  instruction.opcode = OPCODE_PUSH_LITERAL;
  instruction.execute = PushLiteralInstruction_execute;
  return instruction;
}

Instruction create_PopInstruction() {
  Instruction instruction;
  instruction.name = NAME_POP;
  instruction.opcode = OPCODE_POP;
  instruction.execute = PopInstruction_execute;
  return instruction;
}

Instruction create_DelayInstruction() {
  Instruction instruction;
  instruction.name = NAME_DELAY;
  instruction.opcode = OPCODE_DELAY;
  instruction.execute = DelayInstruction_execute;
  return instruction;
}

Instruction create_TopInstruction() {
  Instruction instruction;
  instruction.name = NAME_TOP;
  instruction.opcode = OPCODE_TOP;
  instruction.execute = TopInstruction_execute;
  return instruction;
}

Instruction create_AddInstruction() {
  Instruction instruction;
  instruction.name = NAME_ADD;
  instruction.opcode = OPCODE_ADD;
  instruction.execute = AddInstruction_execute;
  return instruction;
}

Instruction create_SubtractInstruction() {
  Instruction instruction;
  instruction.name = NAME_SUBTRACT;
  instruction.opcode = OPCODE_SUBTRACT;
  instruction.execute = SubtractInstruction_execute;
  return instruction;
}

Instruction create_MultiplyInstruction() {
  Instruction instruction;
  instruction.name = NAME_MULTIPLY;
  instruction.opcode = OPCODE_MULTIPLY;
  instruction.execute = MultiplyInstruction_execute;
  return instruction;
}

Instruction create_DivideInstruction() {
  Instruction instruction;
  instruction.name = NAME_DIVIDE;
  instruction.opcode = OPCODE_DIVIDE;
  instruction.execute = DivideInstruction_execute;
  return instruction;
}

Instruction create_JumpInstruction() {
  Instruction instruction;
  instruction.name = NAME_JUMP;
  instruction.opcode = OPCODE_JUMP;
  instruction.execute = JumpInstruction_execute;
  return instruction;
}

Instruction create_JumpEqualInstruction() {
  Instruction instruction;
  instruction.name = NAME_JUMP_EQUAL;
  instruction.opcode = OPCODE_JUMP_EQUAL;
  instruction.execute = JumpEqualInstruction_execute;
  return instruction;
}

Instruction create_JumpLessInstruction() {
  Instruction instruction;
  instruction.name = NAME_JUMP_LESS;
  instruction.opcode = OPCODE_JUMP_LESS;
  instruction.execute = JumpLessInstruction_execute;
  return instruction;
}

Instruction create_JumpGreaterInstruction() {
  Instruction instruction;
  instruction.name = NAME_JUMP_GREATER;
  instruction.opcode = OPCODE_JUMP_GREATER;
  instruction.execute = JumpGreaterInstruction_execute;
  return instruction;
}

Instruction create_JumpLessEqualInstruction() {
  Instruction instruction;
  instruction.name = NAME_JUMP_LESS_EQUAL;
  instruction.opcode = OPCODE_JUMP_LESS_EQUAL;
  instruction.execute = JumpLessEqualInstruction_execute;
  return instruction;
}

Instruction create_JumpGreaterEqualInstruction() {
  Instruction instruction;
  instruction.name = NAME_JUMP_GREATER_EQUAL;
  instruction.opcode = OPCODE_JUMP_GREATER_EQUAL;
  instruction.execute = JumpGreaterEqualInstruction_execute;
  return instruction;
}

Instruction create_CallInstruction() {
  Instruction instruction;
  instruction.name = NAME_CALL;
  instruction.opcode = OPCODE_CALL;
  instruction.execute = CallInstruction_execute;
  return instruction;
}

Instruction create_ReturnInstruction() {
  Instruction instruction;
  instruction.name = NAME_RET;
  instruction.opcode = OPCODE_RET;
  instruction.execute = ReturnInstruction_execute;
  return instruction;
}

Instruction *create_ISA() {
  static Instruction isa[18];
  isa[OPCODE_HALT] = create_HaltInstruction();
  isa[OPCODE_PUSH] = create_PushInstruction();
  isa[OPCODE_PUSH_LITERAL] = create_PushLiteralInstruction();
  isa[OPCODE_POP] = create_PopInstruction();
  isa[OPCODE_DELAY] = create_DelayInstruction();
  isa[OPCODE_TOP] = create_TopInstruction();
  isa[OPCODE_ADD] = create_AddInstruction();
  isa[OPCODE_SUBTRACT] = create_SubtractInstruction();
  isa[OPCODE_MULTIPLY] = create_MultiplyInstruction();
  isa[OPCODE_DIVIDE] = create_DivideInstruction();
  isa[OPCODE_JUMP] = create_JumpInstruction();
  isa[OPCODE_JUMP_EQUAL] = create_JumpEqualInstruction();
  isa[OPCODE_JUMP_LESS] = create_JumpLessInstruction();
  isa[OPCODE_JUMP_GREATER] = create_JumpGreaterInstruction();
  isa[OPCODE_JUMP_LESS_EQUAL] = create_JumpLessEqualInstruction();
  isa[OPCODE_JUMP_GREATER_EQUAL] = create_JumpGreaterEqualInstruction();
  isa[OPCODE_CALL] = create_CallInstruction();
  isa[OPCODE_RET] = create_ReturnInstruction();
  return isa;
}

long int fetch(Processor *processor) {
  return processor->memory->data[processor->pc];
}

DecodedInstruction decode(long int instruction) {
  DecodedInstruction decoded;
  decoded.opcode = instruction >> 16;
  decoded.operand = instruction & 0xFFFF;
  return decoded;
}

void execute(Processor *processor, int opcode, int operand) {
  Instruction *isa = create_ISA();
  isa[opcode].execute(processor, operand);
  if (opcode != OPCODE_JUMP && opcode != OPCODE_CALL) {
    processor->pc++;
  }
}

long int processor_get_address(Processor *processor, int address) {
  return processor->memory->data[processor->user_memory + address];
}

void processor_set_address(Processor *processor, int address, int value) {
  processor->memory->data[processor->user_memory + address] = value;
}

void run(Processor *processor, long int *program, int program_size,
         bool debug) {
  processor->memory->size = program_size;
  processor->user_memory = program_size;
  for (int i = 0; i < program_size; i++) {
    processor->memory->data[i] = program[i];
  }

  processor->debug = debug;

  if (debug) {
    printf("Running instructions:\n");
    for (int i = 0; i < program_size; i++) {
      printf("%ld\n", program[i]);
    }
    printf("Program size %d bits\n", program_size * 21);
  }

  while (true) {
    long int instruction = fetch(processor);
    DecodedInstruction decoded = decode(instruction);
    execute(processor, decoded.opcode, decoded.operand);
    if (decoded.opcode == OPCODE_HALT) {
      break;
    }
  }
}

Processor *create_processor(int memory_size, int stack_size) {
  Processor *processor = (Processor *)malloc(sizeof(Processor));
  if (processor == NULL) {
    fprintf(stderr, "Memory allocation failed for processor\n");
    exit(1);
  }

  // Allocate memory for memory structure and initialize its data
  Memory *memory = create_memory(memory_size);
  processor->memory = memory;

  // Allocate memory for stack structure and initialize its data
  Stack *stack = create_stack(stack_size);
  processor->stack = stack;

  // Allocate memory for call stack structure and initialize its data
  Stack *call_stack = create_stack(stack_size);
  processor->call_stack = call_stack;
  processor->pc = 0;        // Initialize program counter
  processor->debug = false; // Assuming debug is disabled by default
  processor->user_memory = 0;

  return processor;
}