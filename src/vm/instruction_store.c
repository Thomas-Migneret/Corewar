/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Store instruction execution
*/

#include "my.h"

static void store_in_register(process_t *process, arg_t *destination,
    int value)
{
    if (!is_valid_register(destination->value))
        return;
    set_register_value(process, destination->value, value);
}

static void store_in_memory(vm_t *vm, process_t *process, arg_t *destination,
    int value)
{
    int offset = destination->value % IDX_MOD;

    vm_write_int(vm, process->pc + offset, value);
}

void execute_st(vm_t *vm, process_t *process, arg_t *args)
{
    int value = 0;

    if (!is_valid_register(args[0].value))
        return;
    value = get_register_value(process, args[0].value);
    if (args[1].type == T_REG)
        store_in_register(process, &args[1], value);
    if (args[1].type == T_IND)
        store_in_memory(vm, process, &args[1], value);
}
