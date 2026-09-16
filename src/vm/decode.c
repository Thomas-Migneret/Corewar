/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Instruction argument decoding helpers
*/

#include "my.h"

const op_t *get_instruction_from_opcode(int opcode)
{
    for (int i = 1; op_tab[i].mnemonique != NULL; i++) {
        if (op_tab[i].code == opcode)
            return &op_tab[i];
    }
    return NULL;
}

int instruction_has_coding_byte(int opcode)
{
    return opcode != 1 && opcode != 9 && opcode != 12 && opcode != 15;
}

int get_argument_type(unsigned char coding_byte, int index)
{
    int code = 0;

    if (index < 0 || index >= MAX_ARGS_NUMBER)
        return 0;
    code = (coding_byte >> (6 - index * 2)) & 0x03;
    if (code == 1)
        return T_REG;
    if (code == 2)
        return T_DIR;
    if (code == 3)
        return T_IND;
    return 0;
}

static int is_index_direct(int opcode)
{
    return opcode == 9 || opcode == 10 || opcode == 11 || opcode == 12 ||
        opcode == 14 || opcode == 15;
}

int get_argument_size(int opcode, int type)
{
    if (type == T_REG)
        return 1;
    if (type == T_IND)
        return IND_SIZE;
    if (type == T_DIR && is_index_direct(opcode))
        return IND_SIZE;
    if (type == T_DIR)
        return DIR_SIZE;
    return 0;
}

static int get_coded_instruction_size(vm_t *vm, process_t *process,
    const op_t *instruction)
{
    unsigned char coding_byte = vm_read_byte(vm, process->pc + 1);
    int size = 2;
    int type = 0;

    for (int i = 0; i < instruction->nbr_args; i++) {
        type = get_argument_type(coding_byte, i);
        size += get_argument_size(instruction->code, type);
    }
    return size;
}

int get_instruction_size(vm_t *vm, process_t *process)
{
    const op_t *instruction = get_instruction_from_opcode(
        process->current_opcode);
    int size = 1;

    if (instruction == NULL)
        return size;
    if (instruction_has_coding_byte(instruction->code))
        return get_coded_instruction_size(vm, process, instruction);
    for (int i = 0; i < instruction->nbr_args; i++)
        size += get_argument_size(instruction->code, instruction->type[i]);
    return size;
}
