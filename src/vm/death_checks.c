/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Process death checks
*/

#include "my.h"

static int should_check_processes(vm_t *vm)
{
    if (vm->cycle_to_die <= 0)
        return 0;
    return vm->cycle - vm->last_death_check >= vm->cycle_to_die;
}

static int process_called_live_since_check(vm_t *vm, process_t *process)
{
    return process->last_live_cycle > vm->last_death_check;
}

static void remove_process(process_t **current)
{
    process_t *dead = *current;

    *current = dead->next;
    free(dead);
}

static void remove_dead_processes(vm_t *vm)
{
    process_t **current = &vm->processes;

    while (*current != NULL) {
        if (!process_called_live_since_check(vm, *current))
            remove_process(current);
        else
            current = &(*current)->next;
    }
}

static void update_cycle_to_die(vm_t *vm)
{
    if (vm->live_count >= NBR_LIVE) {
        vm->cycle_to_die -= CYCLE_DELTA;
        vm->live_count = 0;
    }
    if (vm->cycle_to_die <= 0)
        vm->cycle_to_die = 1;
}

void check_process_deaths(vm_t *vm)
{
    if (!should_check_processes(vm))
        return;
    remove_dead_processes(vm);
    update_cycle_to_die(vm);
    vm->last_death_check = vm->cycle;
    if (vm->processes == NULL)
        finish_vm(vm);
}
