/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Jump instruction execution
*/

#include "my.h"

int execute_zjmp(vm_t *vm, process_t *process, arg_t *args)
{
    (void) vm;
    if (!process->carry)
        return 0;
    process->pc = vm_wrap_address(process->pc + (args[0].value % IDX_MOD));
    return 1;
}
