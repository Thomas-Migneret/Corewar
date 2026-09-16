/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Fork instruction execution
*/

#include "my.h"

static void copy_process_state(process_t *child, process_t *process)
{
    child->pc = process->pc;
    for (int i = 0; i < REG_NUMBER; i++)
        child->registers[i] = process->registers[i];
    child->carry = process->carry;
    child->wait_cycles = process->wait_cycles;
    child->current_opcode = process->current_opcode;
    child->is_alive = process->is_alive;
    child->last_live_cycle = process->last_live_cycle;
    child->champ = process->champ;
    child->next = process->next;
}

static void clone_process_at(vm_t *vm, process_t *process, int pc)
{
    process_t *child = malloc(sizeof(process_t));

    if (child == NULL)
        return;
    copy_process_state(child, process);
    child->pc = vm_wrap_address(pc);
    child->wait_cycles = 0;
    child->current_opcode = 0;
    child->next = vm->processes;
    vm->processes = child;
}

void execute_fork(vm_t *vm, process_t *process, arg_t *args)
{
    clone_process_at(vm, process, process->pc + (args[0].value % IDX_MOD));
}

void execute_lfork(vm_t *vm, process_t *process, arg_t *args)
{
    clone_process_at(vm, process, process->pc + args[0].value);
}
