#include "processor.h"
#include "ALU.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int OPCODE_HALT = 0;
int OPCODE_JUMP = 4;
int OPCODE_CALL = 16;

void HaltInstruction_execute(Processor *processor, int operand) { exit(0); }

void PushInstruction_execute(Processor *processor, int address) {
  stack_push(processor->stack, processor->stack->memory.data[address]);
}

void PushLiteralInstruction_execute(Processor *processor, int value) {
  stack_push(processor->stack, value);
}

void PopInstruction_execute(Processor *processor, int address) {
  int value = stack_pop(processor->stack);
  processor_set_address(processor, address, value);
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

void TopInstruction_execute(Processor *processor, int operand) {
  printf("%d\n", stack_get_top(processor->stack));
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

void DelayInstruction_execute(Processor *processor, int value) {
  int microseconds = value * 1000;
  usleep(microseconds);
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
  instruction.name = "HLT";
  instruction.opcode = 0;
  instruction.execute = HaltInstruction_execute;
  return instruction;
}

Instruction create_PushInstruction() {
  Instruction instruction;
  instruction.name = "PSH";
  instruction.opcode = 1;
  instruction.execute = PushInstruction_execute;
  return instruction;
}

Instruction create_PushLiteralInstruction() {
  Instruction instruction;
  instruction.name = "PSHL";
  instruction.opcode = 2;
  instruction.execute = PushLiteralInstruction_execute;
  return instruction;
}

Instruction create_PopInstruction() {
  Instruction instruction;
  instruction.name = "POP";
  instruction.opcode = 3;
  instruction.execute = PopInstruction_execute;
  return instruction;
}

Instruction create_JumpInstruction() {
  Instruction instruction;
  instruction.name = "JMP";
  instruction.opcode = 4;
  instruction.execute = JumpInstruction_execute;
  return instruction;
}

Instruction create_DelayInstruction() {
  Instruction instruction;
  instruction.name = "DLY";
  instruction.opcode = 5;
  instruction.execute = DelayInstruction_execute;
  return instruction;
}

Instruction create_TopInstruction() {
  Instruction instruction;
  instruction.name = "TOP";
  instruction.opcode = 6;
  instruction.execute = TopInstruction_execute;
  return instruction;
}

Instruction create_AddInstruction() {
  Instruction instruction;
  instruction.name = "ADD";
  instruction.opcode = 7;
  instruction.execute = AddInstruction_execute;
  return instruction;
}

Instruction create_SubtractInstruction() {
  Instruction instruction;
  instruction.name = "SUB";
  instruction.opcode = 8;
  instruction.execute = SubtractInstruction_execute;
  return instruction;
}

Instruction create_MultiplyInstruction() {
  Instruction instruction;
  instruction.name = "MUL";
  instruction.opcode = 9;
  instruction.execute = MultiplyInstruction_execute;
  return instruction;
}

Instruction create_DivideInstruction() {
  Instruction instruction;
  instruction.name = "DIV";
  instruction.opcode = 10;
  instruction.execute = DivideInstruction_execute;
  return instruction;
}

Instruction create_JumpEqualInstruction() {
  Instruction instruction;
  instruction.name = "JE";
  instruction.opcode = 11;
  instruction.execute = JumpEqualInstruction_execute;
  return instruction;
}

Instruction create_JumpLessInstruction() {
  Instruction instruction;
  instruction.name = "JL";
  instruction.opcode = 12;
  instruction.execute = JumpLessInstruction_execute;
  return instruction;
}

Instruction create_JumpGreaterInstruction() {
  Instruction instruction;
  instruction.name = "JG";
  instruction.opcode = 13;
  instruction.execute = JumpGreaterInstruction_execute;
  return instruction;
}

Instruction create_JumpLessEqualInstruction() {
  Instruction instruction;
  instruction.name = "JLE";
  instruction.opcode = 14;
  instruction.execute = JumpLessEqualInstruction_execute;
  return instruction;
}

Instruction create_JumpGreaterEqualInstruction() {
  Instruction instruction;
  instruction.name = "JGE";
  instruction.opcode = 15;
  instruction.execute = JumpGreaterEqualInstruction_execute;
  return instruction;
}

Instruction create_CallInstruction() {
  Instruction instruction;
  instruction.name = "CALL";
  instruction.opcode = 16;
  instruction.execute = CallInstruction_execute;
  return instruction;
}

Instruction create_ReturnInstruction() {
  Instruction instruction;
  instruction.name = "RET";
  instruction.opcode = 17;
  instruction.execute = ReturnInstruction_execute;
  return instruction;
}

Instruction *create_ISA() {
  static Instruction isa[18];
  isa[0] = create_HaltInstruction();
  isa[1] = create_PushInstruction();
  isa[2] = create_PushLiteralInstruction();
  isa[3] = create_PopInstruction();
  isa[4] = create_JumpInstruction();
  isa[5] = create_DelayInstruction();
  isa[6] = create_TopInstruction();
  isa[7] = create_AddInstruction();
  isa[8] = create_SubtractInstruction();
  isa[9] = create_MultiplyInstruction();
  isa[10] = create_DivideInstruction();
  isa[11] = create_JumpEqualInstruction();
  isa[12] = create_JumpLessInstruction();
  isa[13] = create_JumpGreaterInstruction();
  isa[14] = create_JumpLessEqualInstruction();
  isa[15] = create_JumpGreaterEqualInstruction();
  isa[16] = create_CallInstruction();
  isa[17] = create_ReturnInstruction();
  return isa;
}

int fetch(Processor *processor) {
  return processor->memory.data[processor->pc];
}

DecodedInstruction decode(int instruction) {
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

int processor_get_address(Processor *processor, int address) {
  return processor->memory.data[processor->user_memory + address];
}

void processor_set_address(Processor *processor, int address, int value) {
  processor->memory.data[processor->user_memory + address] = value;
}

void run(Processor *processor, int *program, int program_size, bool debug) {
  processor->memory.size = program_size;
  processor->user_memory = program_size;
  processor->memory.data = program;
  processor->debug = debug;

  if (debug) {
    printf("Running instructions:\n");
    for (int i = 0; i < program_size; i++) {
      printf("%d\n", program[i]);
    }
    printf("Program size %d bits\n", program_size * 21);
  }

  while (true) {
    int instruction = fetch(processor);
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
  processor->memory = create_memory(memory_size);

  // Allocate memory for stack structure and initialize its data
  Stack stack = create_stack(stack_size);
  processor->stack = &stack;

  // Allocate memory for call stack structure and initialize its data
  Stack call_stack = create_stack(stack_size);
  processor->call_stack = &call_stack;
  processor->pc = 0;        // Initialize program counter
  processor->debug = false; // Assuming debug is disabled by default
  processor->user_memory = 0;

  return processor;
}