/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Live instruction execution
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

static champ_t *find_champion_by_number(vm_t *vm, int number)
{
    for (champ_t *champ = vm->champs; champ != NULL; champ = champ->next) {
        if (champ->prog_number == number)
            return champ;
    }
    return NULL;
}

static void write_live_message(champ_t *champ)
{
    write_text("The player ");
    write_number(champ->prog_number);
    write_text("(");
    if (champ->name != NULL)
        write_text(champ->name);
    write_text(")is alive.\n");
}

void execute_live(vm_t *vm, process_t *process, arg_t *args)
{
    champ_t *champ = find_champion_by_number(vm, args[0].value);

    process->is_alive = 1;
    process->last_live_cycle = vm->cycle;
    vm->live_count++;
    if (champ == NULL)
        return;
    vm->last_live_champ = champ;
    write_live_message(champ);
}
