#include "processor.h"

int main_processor()
{

    int memory_size = 32;
    int stack_size = 32;
    int total_ports = 4;

    Processor *processor = processor_create(memory_size, stack_size, total_ports);
    // blink led
    int program_size = 27;
    long int program[] = {131074, 196608, 131073, 131072, 1441792, 65537, 1179648, 196612, 131072, 720900, 655372, 655379, 65537, 131073, 131073, 1441792, 1245184, 196609, 655362, 65537, 131073, 131073, 1441792, 1376256, 1179648, 196609, 655362};

    processor_run(processor, program, program_size, false);
    return 0;
}

int main() { return main_processor(); }
