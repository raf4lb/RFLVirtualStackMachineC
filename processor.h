#include "io.h"
#include "stack.h"
#include <stdbool.h>

typedef struct
{
    Memory *memory;
    Stack *stack;
    Stack *call_stack;
    int pc;
    PortBank *port_bank;
    int user_memory;
    bool debug;
} Processor;

typedef struct
{
    int opcode;
    int operand;
} DecodedInstruction;

long int processor_fetch(Processor *processor);

DecodedInstruction processor_decode(long int instruction);

void processor_execute(Processor *processor, int opcode, int operand);

long int processor_get_address(Processor *processor, int address);

void processor_set_address(Processor *processor, int address, int value);

void processor_set_pc(Processor *processor, int address);

void processor_load_program(Processor *processor, long int *program,
                            int program_size);

void processor_run(Processor *processor, long int *program, int program_size,
                   bool debug);

Processor *processor_create(int memory_size, int stack_size, int total_ports);

void processor_free(Processor *processor);

void processor_get_state(Processor *processor);

// Instruction structure
typedef struct
{
    char *name;
    int opcode;
    void (*execute)(Processor *, int);
} Instruction;

// Instruction definitions
void HaltInstruction_execute(Processor *, int);
void PushInstruction_execute(Processor *, int);
void PushLiteralInstruction_execute(Processor *, int);
void PopInstruction_execute(Processor *, int);
void DelayInstruction_execute(Processor *, int);
void TopInstruction_execute(Processor *, int);
void AddInstruction_execute(Processor *, int);
void SubtractInstruction_execute(Processor *, int);
void MultiplyInstruction_execute(Processor *, int);
void DivideInstruction_execute(Processor *, int);
void JumpInstruction_execute(Processor *, int);
void JumpEqualInstruction_execute(Processor *, int);
void JumpLessInstruction_execute(Processor *, int);
void JumpGreaterInstruction_execute(Processor *, int);
void JumpLessEqualInstruction_execute(Processor *, int);
void JumpGreaterEqualInstruction_execute(Processor *, int);
void CallInstruction_execute(Processor *, int);
void ReturnInstruction_execute(Processor *, int);
void AndInstruction_execute(Processor *, int);
void OrInstruction_execute(Processor *, int);
void XorInstruction_execute(Processor *, int);
void NotInstruction_execute(Processor *, int);
void LeftShiftInstruction_execute(Processor *, int);
void RightShiftInstruction_execute(Processor *, int);

Instruction create_HaltInstruction();
Instruction create_PushInstruction();
Instruction create_PushLiteralInstruction();
Instruction create_PopInstruction();
Instruction create_DelayInstruction();
Instruction create_TopInstruction();
Instruction create_AddInstruction();
Instruction create_SubtractInstruction();
Instruction create_MultiplyInstruction();
Instruction create_DivideInstruction();
Instruction create_JumpInstruction();
Instruction create_JumpEqualInstruction();
Instruction create_JumpLessInstruction();
Instruction create_JumpGreaterInstruction();
Instruction create_JumpLessEqualInstruction();
Instruction create_JumpGreaterEqualInstruction();
Instruction create_CallInstruction();
Instruction create_AndInstruction();
Instruction create_OrInstruction();
Instruction create_XorInstruction();
Instruction create_NotInstruction();
Instruction create_LeftShiftInstruction();
Instruction create_RightShiftInstruction();

Instruction *create_ISA();
