#define _DDRB 0
#define _PORTB 1

typedef struct
{
    volatile unsigned char **ports;
    int size;
} PortBank;

void set_port(int address, int value);

void map_ports(PortBank *port_bank);

PortBank *create_port_bank(int ports);