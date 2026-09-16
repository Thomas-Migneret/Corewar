/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Virtual machine game loop
*/

#include "my.h"

static int should_dump(vm_t *vm)
{
    return vm->dump_cycle >= 0 && vm->cycle == vm->dump_cycle;
}

void run_vm(vm_t *vm)
{
    if (vm->processes == NULL)
        finish_vm(vm);
    while (!vm->is_finished) {
        if (should_dump(vm)) {
            dump_arena(vm);
            return;
        }
        run_vm_cycle(vm);
    }
}
