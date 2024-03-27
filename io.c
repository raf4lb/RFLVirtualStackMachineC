#include "io.h"
#include "avr/io.h"
#include <stdio.h>
#include <stdlib.h>
#include "serial.h"

void map_ports(PortBank *port_bank)
{
    // port_bank->ports = {&DDRB, &PORTB};
    port_bank->ports[0] = &DDRB;
    port_bank->ports[1] = &PORTB;
    port_bank->ports[2] = &PINB;
    port_bank->ports[3] = &PORTD;
}

PortBank *port_bank_create(int size)
{
    PortBank *port_bank = (PortBank *)malloc(sizeof(PortBank));
    if (port_bank == NULL)
    {
        serial_printf("Memory allocation failed for port bank\n");
        exit(1);
    }
    port_bank->size = size;
    port_bank->ports = (volatile unsigned char **)malloc(size * sizeof(volatile unsigned char *));
    if (port_bank->ports == NULL)
    {
        serial_printf("Memory allocation failed for ports of the bank\n");
        exit(1);
    }
    map_ports(port_bank);
    return port_bank;
}

void port_bank_pprint(PortBank *port_bank)
{
    serial_printf("[");
    for (int i = 0; i < port_bank->size; i++)
    {
        if (i > 0)
            serial_printf(", ");
        serial_printf("%hhu", *(port_bank->ports[i]));
    }
    serial_printf("]\n");
}

void port_bank_free(PortBank *port_bank)
{
    free(port_bank->ports);
    free(port_bank);
}