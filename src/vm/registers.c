/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Process register helpers
*/

#include "my.h"

int is_valid_register(int reg)
{
    return reg >= 1 && reg <= REG_NUMBER;
}

int get_register_value(process_t *process, int reg)
{
    if (!is_valid_register(reg))
        return 0;
    return process->registers[reg - 1];
}

void set_register_value(process_t *process, int reg, int value)
{
    if (!is_valid_register(reg))
        return;
    process->registers[reg - 1] = value;
}
