/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Winner output handling
*/

#include "my.h"

static void write_text(char *text)
{
    write(1, text, my_strlen(text));
}

static void write_unsigned_number(unsigned int number)
{
    char digit = 0;

    if (number >= 10)
        write_unsigned_number(number / 10);
    digit = number % 10 + '0';
    write(1, &digit, 1);
}

static void write_number(int value)
{
    unsigned int number = value;

    if (value < 0) {
        write(1, "-", 1);
        number = -number;
    }
    write_unsigned_number(number);
}

static void write_winner(champ_t *champ)
{
    write_text("The player ");
    write_number(champ->prog_number);
    write_text("(");
    if (champ->name != NULL)
        write_text(champ->name);
    write_text(")has won.\n");
}

void finish_vm(vm_t *vm)
{
    if (vm->is_finished)
        return;
    vm->is_finished = 1;
    if (vm->last_live_champ != NULL)
        write_winner(vm->last_live_champ);
}
