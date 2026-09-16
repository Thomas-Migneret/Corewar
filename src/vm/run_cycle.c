/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Virtual machine execution cycle skeleton
*/

#include "my.h"

static void skip_invalid_opcode(process_t *process)
{
    process->pc = vm_wrap_address(process->pc + 1);
    process->current_opcode = 0;
    process->wait_cycles = 0;
}

static void run_waiting_process(vm_t *vm, process_t *process)
{
    if (process->wait_cycles <= 0)
        return;
    process->wait_cycles--;
    if (process->wait_cycles == 0 && process->current_opcode != 0)
        execute_instruction(vm, process);
}

static void schedule_process(vm_t *vm, process_t *process)
{
    unsigned char opcode = vm_read_byte(vm, process->pc);
    const op_t *instruction = get_instruction_from_opcode(opcode);

    if (instruction == NULL) {
        skip_invalid_opcode(process);
        return;
    }
    process->current_opcode = opcode;
    process->wait_cycles = instruction->nbr_cycles;
}

void run_vm_cycle(vm_t *vm)
{
    vm->cycle++;
    for (process_t *process = vm->processes; process != NULL;
        process = process->next) {
        if (process->wait_cycles > 0)
            run_waiting_process(vm, process);
        else
            schedule_process(vm, process);
    }
    check_process_deaths(vm);
}
