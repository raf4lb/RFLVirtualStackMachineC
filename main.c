#include "processor.h"

int main_processor() {

  int memory_size = 32;
  int stack_size = 32;
  int total_ports = 4;

  Processor *processor = processor_create(memory_size, stack_size, total_ports);
  // blink led
  int program_size = 33;
  long int program[] = {131128,  196608,  131200,  196610,  1048606, 1048591,
                        262644,  1048594, 262644,  1048603, 1048597, 262644,
                        1048600, 262644,  655364,  131120,  196609,  1114112,
                        131112,  196609,  1114112, 131088,  196609,  1114112,
                        131080,  196609,  1114112, 131200,  196611,  1114112,
                        131072,  196611,  1114112};

  processor_run(processor, program, program_size, false);
  return 0;
}

int main() { return main_processor(); }
