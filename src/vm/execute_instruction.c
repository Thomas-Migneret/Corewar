/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Instruction execution dispatcher
*/

#include "my.h"

static int execute_low_opcode(vm_t *vm, process_t *process, arg_t *args)
{
    if (process->current_opcode == 1)
        execute_live(vm, process, args);
    if (process->current_opcode == 2)
        execute_ld(vm, process, args);
    if (process->current_opcode == 3)
        execute_st(vm, process, args);
    if (process->current_opcode == 4)
        execute_add(vm, process, args);
    if (process->current_opcode == 5)
        execute_sub(vm, process, args);
    return 0;
}

static int execute_mid_opcode(vm_t *vm, process_t *process,
    arg_t *args)
{
    if (process->current_opcode == 6)
        execute_and(vm, process, args);
    if (process->current_opcode == 7)
        execute_or(vm, process, args);
    if (process->current_opcode == 8)
        execute_xor(vm, process, args);
    if (process->current_opcode == 9)
        return execute_zjmp(vm, process, args);
    return 0;
}

static int execute_high_opcode(vm_t *vm, process_t *process,
    arg_t *args)
{
    if (process->current_opcode == 10)
        execute_ldi(vm, process, args);
    if (process->current_opcode == 11)
        execute_sti(vm, process, args);
    if (process->current_opcode == 12)
        execute_fork(vm, process, args);
    if (process->current_opcode == 13)
        execute_lld(vm, process, args);
    if (process->current_opcode == 14)
        execute_lldi(vm, process, args);
    if (process->current_opcode == 15)
        execute_lfork(vm, process, args);
    if (process->current_opcode == 16)
        execute_print(vm, process, args);
    return 0;
}

static int execute_known_instruction(vm_t *vm, process_t *process,
    arg_t *args)
{
    if (process->current_opcode <= 5)
        return execute_low_opcode(vm, process, args);
    if (process->current_opcode <= 9)
        return execute_mid_opcode(vm, process, args);
    return execute_high_opcode(vm, process, args);
}

void execute_instruction(vm_t *vm, process_t *process)
{
    arg_t args[MAX_ARGS_NUMBER];
    int size = get_instruction_size(vm, process);
    int did_jump = 0;

    if (read_instruction_args(vm, process, args) == 0)
        did_jump = execute_known_instruction(vm, process, args);
    if (!did_jump)
        process->pc = vm_wrap_address(process->pc + size);
    process->current_opcode = 0;
}
