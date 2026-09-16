/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Binary instruction execution
*/

#include "my.h"

static int read_binary_value(vm_t *vm, process_t *process, arg_t *arg,
    int *value)
{
    if (arg->type == T_REG && !is_valid_register(arg->value))
        return 84;
    if (arg->type == T_REG)
        *value = get_register_value(process, arg->value);
    if (arg->type == T_DIR)
        *value = arg->value;
    if (arg->type == T_IND)
        *value = vm_read_int(vm, process->pc + (arg->value % IDX_MOD));
    return 0;
}

static void write_binary_result(process_t *process, arg_t *args, int value)
{
    if (!is_valid_register(args[2].value))
        return;
    set_register_value(process, args[2].value, value);
    process->carry = value == 0;
}

static int read_binary_args(vm_t *vm, process_t *process, arg_t *args,
    int *values)
{
    if (read_binary_value(vm, process, &args[0], &values[0]) == 84)
        return 84;
    if (read_binary_value(vm, process, &args[1], &values[1]) == 84)
        return 84;
    return 0;
}

void execute_and(vm_t *vm, process_t *process, arg_t *args)
{
    int values[2];

    values[0] = 0;
    values[1] = 0;
    if (read_binary_args(vm, process, args, values) == 84)
        return;
    write_binary_result(process, args, values[0] & values[1]);
}

void execute_or(vm_t *vm, process_t *process, arg_t *args)
{
    int values[2];

    values[0] = 0;
    values[1] = 0;
    if (read_binary_args(vm, process, args, values) == 84)
        return;
    write_binary_result(process, args, values[0] | values[1]);
}

void execute_xor(vm_t *vm, process_t *process, arg_t *args)
{
    int values[2];

    values[0] = 0;
    values[1] = 0;
    if (read_binary_args(vm, process, args, values) == 84)
        return;
    write_binary_result(process, args, values[0] ^ values[1]);
}
