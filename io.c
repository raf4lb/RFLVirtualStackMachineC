#include "io.h"
#include "avr/io.h"
#include <stdio.h>
#include <stdlib.h>

void set_port(int address, int value)
{
    switch (address)
    {
    case _DDRB:
        DDRB = value;
        break;
    case _PORTB:
        PORTB = value;
        break;
    default:
        break;
    }
}

void map_ports(PortBank *port_bank)
{
    // port_bank->ports = {&DDRB, &PORTB};
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
    map_ports(port_bank);
    return port_bank;
}