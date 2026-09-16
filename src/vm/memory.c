/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Circular arena memory helpers
*/

#include "my.h"

int vm_wrap_address(int address)
{
    int result = address % MEM_SIZE;

    if (result < 0)
        result += MEM_SIZE;
    return result;
}

unsigned char vm_read_byte(vm_t *vm, int address)
{
    return vm->arena[vm_wrap_address(address)];
}

int vm_read_short(vm_t *vm, int address)
{
    int value = 0;

    value = vm_read_byte(vm, address) << 8;
    value |= vm_read_byte(vm, address + 1);
    if ((value & 0x8000) != 0)
        value -= 0x10000;
    return value;
}

int vm_read_int(vm_t *vm, int address)
{
    unsigned int value = 0;

    value = (unsigned int) vm_read_byte(vm, address) << 24;
    value |= (unsigned int) vm_read_byte(vm, address + 1) << 16;
    value |= (unsigned int) vm_read_byte(vm, address + 2) << 8;
    value |= vm_read_byte(vm, address + 3);
    return (int) value;
}

void vm_write_int(vm_t *vm, int address, int value)
{
    unsigned int bytes = (unsigned int) value;

    vm->arena[vm_wrap_address(address)] = (bytes >> 24) & 0xFF;
    vm->arena[vm_wrap_address(address + 1)] = (bytes >> 16) & 0xFF;
    vm->arena[vm_wrap_address(address + 2)] = (bytes >> 8) & 0xFF;
    vm->arena[vm_wrap_address(address + 3)] = bytes & 0xFF;
}
