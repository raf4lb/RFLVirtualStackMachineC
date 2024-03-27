#define _DDRB 0
#define _PORTB 1

typedef struct
{
    volatile unsigned char **ports;
    int size;
} PortBank;

void map_ports(PortBank *port_bank);

PortBank *create_port_bank(int ports);