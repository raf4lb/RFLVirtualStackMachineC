#include "ALU.h"
#include "processor.h"

int main_processor() {
  Processor *processor = create_processor(32, 32);
  // blink led
  int program_size = 9;
  long int program[] = {131073, 327680, 196608, 263144, 131072,
                   327680, 263144, 196608, 655360};

  run(processor, program, program_size, false);
  return 0;
}

int main() { return main_processor(); }
