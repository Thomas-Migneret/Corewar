/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Indirect store instruction execution
*/

#include "my.h"

static int read_sti_index(vm_t *vm, process_t *process, arg_t *arg,
    int *value)
{
    if (arg->type == T_REG && !is_valid_register(arg->value))
        return 84;
    if (arg->type == T_REG)
        *value = get_register_value(process, arg->value);
    if (arg->type == T_DIR)
        *value = arg->value;
    if (arg->type == T_IND)
        *value = vm_read_short(vm, process->pc + (arg->value % IDX_MOD));
    return 0;
}

static int read_sti_offsets(vm_t *vm, process_t *process, arg_t *args,
    int *offsets)
{
    if (read_sti_index(vm, process, &args[1], &offsets[0]) == 84)
        return 84;
    return read_sti_index(vm, process, &args[2], &offsets[1]);
}

void execute_sti(vm_t *vm, process_t *process, arg_t *args)
{
    int offsets[2];
    int value = 0;
    int address = 0;

    offsets[0] = 0;
    offsets[1] = 0;
    if (!is_valid_register(args[0].value))
        return;
    if (read_sti_offsets(vm, process, args, offsets) == 84)
        return;
    value = get_register_value(process, args[0].value);
    address = process->pc + ((offsets[0] + offsets[1]) % IDX_MOD);
    vm_write_int(vm, address, value);
}
