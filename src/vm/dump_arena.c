/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Arena dump display
*/

#include "my.h"

static void write_char(char c)
{
    write(1, &c, 1);
}

static void write_hex(unsigned int value, int size)
{
    char const *base = "0123456789ABCDEF";
    int shift = (size - 1) * 4;

    while (shift >= 0) {
        write_char(base[(value >> shift) & 0xF]);
        shift -= 4;
    }
}

static void write_header_values(void)
{
    write(1, "Memory:   ", 10);
    for (int i = 0; i < 32; i++) {
        write_hex(i, 2);
        if (i < 31)
            write_char(' ');
    }
    write_char('\n');
}

static void write_header_separator(void)
{
    write(1, "          ", 10);
    for (int i = 0; i < 32; i++) {
        write(1, "--", 2);
        if (i < 31)
            write_char(' ');
    }
    write_char('\n');
}

static void dump_line(vm_t *vm, int address)
{
    write_hex(address, 8);
    write(1, ": ", 2);
    for (int i = 0; i < 32; i++) {
        write_hex(vm->arena[address + i], 2);
        if (i < 31)
            write_char(' ');
    }
    write_char('\n');
}

void dump_arena(vm_t *vm)
{
    write_header_values();
    write_header_separator();
    for (int i = 0; i < MEM_SIZE; i += 32)
        dump_line(vm, i);
}
