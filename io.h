#define _DDRB 0
#define _PORTB 1

typedef struct
{
    volatile unsigned char **ports;
    int size;
} PortBank;

void map_ports(PortBank *port_bank);

PortBank *port_bank_create(int ports);

void port_bank_pprint(PortBank *port_bank);

void port_bank_free(PortBank *port_bank);