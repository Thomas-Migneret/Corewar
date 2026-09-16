/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Print instruction execution
*/

#include "my.h"

void execute_print(vm_t *vm, process_t *process, arg_t *args)
{
    unsigned char character = 0;

    (void) vm;
    if (!is_valid_register(args[0].value))
        return;
    character = get_register_value(process, args[0].value);
    write(1, &character, 1);
}
