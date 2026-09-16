/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Process initialization from loaded champions
*/

#include "my.h"

static void clear_registers(int *registers)
{
    for (int i = 0; i < REG_NUMBER; i++)
        registers[i] = 0;
}

static process_t *create_process(champ_t *champ)
{
    process_t *process = malloc(sizeof(process_t));

    if (process == NULL)
        return NULL;
    process->pc = vm_wrap_address(champ->load_address);
    clear_registers(process->registers);
    process->registers[0] = champ->prog_number;
    process->carry = 0;
    process->wait_cycles = 0;
    process->current_opcode = 0;
    process->is_alive = 1;
    process->last_live_cycle = 0;
    process->champ = champ;
    process->next = NULL;
    return process;
}

static void append_process(vm_t *vm, process_t *process)
{
    process_t *current = vm->processes;

    if (process == NULL)
        return;
    if (vm->processes == NULL) {
        vm->processes = process;
        return;
    }
    while (current->next != NULL)
        current = current->next;
    current->next = process;
}

void init_processes(vm_t *vm)
{
    process_t *process = NULL;

    vm->processes = NULL;
    for (champ_t *champ = vm->champs; champ != NULL; champ = champ->next) {
        process = create_process(champ);
        append_process(vm, process);
    }
}
