#include "processor.h"

int main_processor()
{

    int memory_size = 32;
    int stack_size = 32;
    int total_ports = 4;

    Processor *processor = processor_create(memory_size, stack_size, total_ports);
    // blink led
    int program_size = 23;
    long int program[] = {131128, 196608, 1048587, 262644, 1048590, 262644, 1048593, 262644, 1048596, 262644, 655362, 131120, 196609, 1114112, 131112, 196609, 1114112, 131088, 196609, 1114112, 131080, 196609, 1114112};

    processor_run(processor, program, program_size, false);
    return 0;
}

int main() { return main_processor(); }
