/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Champion loading into arena
*/

#include "my.h"

static int count_champions(champ_t *champs)
{
    int count = 0;

    for (champ_t *champ = champs; champ != NULL; champ = champ->next)
        count++;
    return count;
}

void set_champions_load_addresses(vm_t *vm)
{
    int count = count_champions(vm->champs);
    int step = 0;
    int index = 0;

    if (count <= 0)
        return;
    step = MEM_SIZE / count;
    for (champ_t *champ = vm->champs; champ != NULL; champ = champ->next) {
        if (champ->load_address < 0)
            champ->load_address = index * step;
        index++;
    }
}

static void load_champ_code(vm_t *vm, champ_t *champ)
{
    int address = 0;

    if (champ->code == NULL || champ->prog_size <= 0)
        return;
    if (champ->load_address < 0)
        return;
    address = vm_wrap_address(champ->load_address);
    for (int i = 0; i < champ->prog_size; i++)
        vm->arena[vm_wrap_address(address + i)] = champ->code[i];
}

void load_champions(vm_t *vm)
{
    for (champ_t *champ = vm->champs; champ != NULL; champ = champ->next)
        load_champ_code(vm, champ);
}
