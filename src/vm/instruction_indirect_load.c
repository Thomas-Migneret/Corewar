/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Indirect load instruction execution
*/

#include "my.h"

static int read_index_value(vm_t *vm, process_t *process, arg_t *arg,
    int *value)
{
    int offset = arg->value;

    if (arg->type == T_REG && !is_valid_register(arg->value))
        return 84;
    if (arg->type == T_REG)
        *value = get_register_value(process, arg->value);
    if (arg->type == T_DIR)
        *value = arg->value;
    if (arg->type == T_IND) {
        if (process->current_opcode == 10)
            offset %= IDX_MOD;
        *value = vm_read_short(vm, process->pc + offset);
    }
    return 0;
}

static int read_index_args(vm_t *vm, process_t *process, arg_t *args,
    int *values)
{
    if (!is_valid_register(args[2].value))
        return 84;
    if (read_index_value(vm, process, &args[0], &values[0]) == 84)
        return 84;
    return read_index_value(vm, process, &args[1], &values[1]);
}

static void write_index_result(process_t *process, int reg, int value)
{
    set_register_value(process, reg, value);
    process->carry = value == 0;
}

void execute_ldi(vm_t *vm, process_t *process, arg_t *args)
{
    int values[2];
    int value = 0;
    int offset = 0;

    values[0] = 0;
    values[1] = 0;
    if (read_index_args(vm, process, args, values) == 84)
        return;
    offset = (values[0] + values[1]) % IDX_MOD;
    value = vm_read_int(vm, process->pc + offset);
    write_index_result(process, args[2].value, value);
}

void execute_lldi(vm_t *vm, process_t *process, arg_t *args)
{
    int values[2];
    int value = 0;

    values[0] = 0;
    values[1] = 0;
    if (read_index_args(vm, process, args, values) == 84)
        return;
    value = vm_read_int(vm, process->pc + values[0] + values[1]);
    write_index_result(process, args[2].value, value);
}
