#include "io.h"
#include <stdio.h>
#include <stdlib.h>

volatile unsigned char DDRB;
volatile unsigned char PORTB;
volatile unsigned char DDRD;
volatile unsigned char PORTD;

void map_ports(PortBank *port_bank)
{
    port_bank->ports[0] = &DDRB;
    port_bank->ports[1] = &PORTB;
    port_bank->ports[2] = &DDRD;
    port_bank->ports[3] = &PORTD;
}

PortBank *create_port_bank(int size)
{
    PortBank *port_bank = (PortBank *)malloc(sizeof(PortBank));
    if (port_bank == NULL)
    {
        fprintf(stderr, "Memory allocation failed for port bank\n");
        exit(1);
    }
    port_bank->size = size;
    port_bank->ports = (volatile unsigned char **)malloc(size * sizeof(volatile unsigned char *));
    if (port_bank->ports == NULL)
    {
        printf("Memory allocation failed for ports of the bank\n");
        exit(1);
    }
    if (size > 0)
    {
        map_ports(port_bank);
    }
    return port_bank;
}