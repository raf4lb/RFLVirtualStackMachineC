#include "stack.h"
#include <stdbool.h>

typedef struct {
  Memory memory;
  Stack *stack;
  Stack *call_stack;
  int pc;
  int user_memory;
  bool debug;
} Processor;

typedef struct {
  int opcode;
  int operand;
} DecodedInstruction;

DecodedInstruction decode(int instruction);

int processor_get_address(Processor *processor, int address);

void processor_set_address(Processor *processor, int address, int value);

int fetch(Processor *processor);

void execute(Processor *processor, int opcode, int operand);

Processor *create_processor(int memory_size, int stack_size);

void run(Processor *processor, int *program, int program_size, bool debug);

// Instruction structure
typedef struct {
  char *name;
  int opcode;
  void (*execute)(Processor *, int);
} Instruction;

// Instruction definitions
void HaltInstruction_execute(Processor *, int);
void PushInstruction_execute(Processor *, int);
void PushLiteralInstruction_execute(Processor *, int);
void PopInstruction_execute(Processor *, int);
void AddInstruction_execute(Processor *, int);
void SubtractInstruction_execute(Processor *, int);
void MultiplyInstruction_execute(Processor *, int);
void DivideInstruction_execute(Processor *, int);
void TopInstruction_execute(Processor *, int);
void JumpInstruction_execute(Processor *, int);
void JumpEqualInstruction_execute(Processor *, int);
void JumpLessInstruction_execute(Processor *, int);
void JumpGreaterInstruction_execute(Processor *, int);
void JumpLessEqualInstruction_execute(Processor *, int);
void JumpGreaterEqualInstruction_execute(Processor *, int);
void DelayInstruction_execute(Processor *, int);
void CallInstruction_execute(Processor *, int);
void ReturnInstruction_execute(Processor *, int);

Instruction create_HaltInstruction();
Instruction create_PushInstruction();
Instruction create_PushLiteralInstruction();
Instruction create_PopInstruction();
Instruction create_JumpInstruction();
Instruction create_DelayInstruction();
Instruction create_TopInstruction();
Instruction create_AddInstruction();
Instruction create_SubtractInstruction();
Instruction create_MultiplyInstruction();
Instruction create_DivideInstruction();
Instruction create_JumpEqualInstruction();
Instruction create_JumpLessInstruction();
Instruction create_JumpGreaterInstruction();
Instruction create_JumpLessEqualInstruction();
Instruction create_JumpGreaterEqualInstruction();
Instruction create_CallInstruction();
Instruction create_ReturnInstruction();

Instruction *create_ISA();