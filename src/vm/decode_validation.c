/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Instruction argument validation helpers
*/

#include "my.h"

int are_instruction_arguments_valid(vm_t *vm, process_t *process)
{
    const op_t *instruction = get_instruction_from_opcode(
        process->current_opcode);
    unsigned char coding_byte = 0;
    int type = 0;

    if (instruction == NULL)
        return 0;
    if (!instruction_has_coding_byte(instruction->code))
        return 1;
    coding_byte = vm_read_byte(vm, process->pc + 1);
    for (int i = 0; i < instruction->nbr_args; i++) {
        type = get_argument_type(coding_byte, i);
        if ((instruction->type[i] & type) == 0)
            return 0;
    }
    return 1;
}
