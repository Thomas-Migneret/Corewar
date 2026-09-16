/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Arithmetic instruction execution
*/

#include "my.h"

static int are_registers_valid(arg_t *args)
{
    return is_valid_register(args[0].value) &&
        is_valid_register(args[1].value) &&
        is_valid_register(args[2].value);
}

static void set_arithmetic_result(process_t *process, arg_t *args,
    unsigned int result)
{
    set_register_value(process, args[2].value, (int) result);
    process->carry = result == 0;
}

void execute_add(vm_t *vm, process_t *process, arg_t *args)
{
    unsigned int left = 0;
    unsigned int right = 0;

    (void) vm;
    if (!are_registers_valid(args))
        return;
    left = (unsigned int) get_register_value(process, args[0].value);
    right = (unsigned int) get_register_value(process, args[1].value);
    set_arithmetic_result(process, args, left + right);
}

void execute_sub(vm_t *vm, process_t *process, arg_t *args)
{
    unsigned int left = 0;
    unsigned int right = 0;

    (void) vm;
    if (!are_registers_valid(args))
        return;
    left = (unsigned int) get_register_value(process, args[0].value);
    right = (unsigned int) get_register_value(process, args[1].value);
    set_arithmetic_result(process, args, left - right);
}
