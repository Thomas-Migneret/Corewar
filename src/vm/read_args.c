/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Instruction argument reader
*/

#include "my.h"

static void clear_args(arg_t *args)
{
    for (int i = 0; i < MAX_ARGS_NUMBER; i++) {
        args[i].type = 0;
        args[i].size = 0;
        args[i].value = 0;
    }
}

static int get_instruction_arg_type(vm_t *vm, process_t *process,
    const op_t *instruction, int index)
{
    unsigned char coding_byte = 0;

    if (!instruction_has_coding_byte(instruction->code))
        return instruction->type[index];
    coding_byte = vm_read_byte(vm, process->pc + 1);
    return get_argument_type(coding_byte, index);
}

static int read_arg_value(vm_t *vm, int address, int size)
{
    if (size == 1)
        return vm_read_byte(vm, address);
    if (size == IND_SIZE)
        return vm_read_short(vm, address);
    if (size == DIR_SIZE)
        return vm_read_int(vm, address);
    return 0;
}

static void read_args_values(vm_t *vm, process_t *process, arg_t *args,
    const op_t *instruction)
{
    int offset = 1 + instruction_has_coding_byte(instruction->code);

    for (int i = 0; i < instruction->nbr_args; i++) {
        args[i].type = get_instruction_arg_type(vm, process, instruction, i);
        args[i].size = get_argument_size(instruction->code, args[i].type);
        args[i].value = read_arg_value(vm, process->pc + offset,
            args[i].size);
        offset += args[i].size;
    }
}

int read_instruction_args(vm_t *vm, process_t *process, arg_t *args)
{
    const op_t *instruction = get_instruction_from_opcode(
        process->current_opcode);

    clear_args(args);
    if (instruction == NULL)
        return 84;
    if (!are_instruction_arguments_valid(vm, process))
        return 84;
    read_args_values(vm, process, args, instruction);
    return 0;
}
