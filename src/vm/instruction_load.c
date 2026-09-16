/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Load instruction execution
*/

#include "my.h"

static int read_load_value(vm_t *vm, process_t *process, arg_t *arg,
    int use_idx_mod)
{
    int offset = arg->value;

    if (arg->type == T_DIR)
        return arg->value;
    if (use_idx_mod)
        offset %= IDX_MOD;
    return vm_read_int(vm, process->pc + offset);
}

static void write_load_result(process_t *process, int reg, int value)
{
    set_register_value(process, reg, value);
    process->carry = value == 0;
}

void execute_ld(vm_t *vm, process_t *process, arg_t *args)
{
    int value = 0;

    if (!is_valid_register(args[1].value))
        return;
    value = read_load_value(vm, process, &args[0], 1);
    write_load_result(process, args[1].value, value);
}

void execute_lld(vm_t *vm, process_t *process, arg_t *args)
{
    int value = 0;

    if (!is_valid_register(args[1].value))
        return;
    value = read_load_value(vm, process, &args[0], 0);
    write_load_result(process, args[1].value, value);
}
