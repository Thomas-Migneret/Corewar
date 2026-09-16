/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Virtual machine initialization
*/

#include "my.h"

static void clear_arena(unsigned char *arena)
{
    for (int i = 0; i < MEM_SIZE; i++)
        arena[i] = 0;
}

void init_vm(vm_t *vm, data_t *data)
{
    clear_arena(vm->arena);
    vm->cycle = 0;
    vm->dump_cycle = data->cycle;
    vm->cycle_to_die = CYCLE_TO_DIE;
    vm->last_death_check = 0;
    vm->live_count = 0;
    vm->is_finished = 0;
    vm->champs = data->champs;
    vm->last_live_champ = NULL;
    vm->processes = NULL;
    set_champions_load_addresses(vm);
    load_champions(vm);
    init_processes(vm);
}
