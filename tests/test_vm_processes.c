/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Unit tests for VM process initialization
*/

#include <criterion/criterion.h>
#include "my.h"

static void setup_champ(champ_t *champ, int prog_number)
{
    champ->path = "test.cor";
    champ->name = "test";
    champ->prog_number = prog_number;
    champ->load_address = -1;
    champ->prog_size = 0;
    champ->code = NULL;
    champ->next = NULL;
}

static void setup_data(data_t *data, champ_t *champ)
{
    data->cycle = -1;
    data->champs = champ;
}

static void assert_empty_registers_after_first(process_t *process)
{
    for (int i = 1; i < REG_NUMBER; i++)
        cr_assert_eq(process->registers[i], 0);
}

Test(init_processes, creates_one_process_per_champion)
{
    champ_t first = {0};
    champ_t second = {0};
    data_t data = {0};
    vm_t vm;

    setup_champ(&first, 1);
    setup_champ(&second, 2);
    first.next = &second;
    setup_data(&data, &first);
    init_vm(&vm, &data);
    cr_assert_not_null(vm.processes);
    cr_assert_not_null(vm.processes->next);
    cr_assert_null(vm.processes->next->next);
}

Test(init_processes, initializes_process_state_from_champion)
{
    champ_t champ = {0};
    data_t data = {0};
    vm_t vm;

    setup_champ(&champ, 7);
    champ.load_address = 123;
    setup_data(&data, &champ);
    init_vm(&vm, &data);
    cr_assert_not_null(vm.processes);
    cr_assert_eq(vm.processes->pc, 123);
    cr_assert_eq(vm.processes->registers[0], 7);
    cr_assert_eq(vm.processes->carry, 0);
    cr_assert_eq(vm.processes->wait_cycles, 0);
    cr_assert_eq(vm.processes->is_alive, 1);
    cr_assert_eq(vm.processes->last_live_cycle, 0);
    cr_assert_eq(vm.processes->champ, &champ);
    assert_empty_registers_after_first(vm.processes);
}

Test(init_processes, uses_default_champion_addresses)
{
    champ_t first = {0};
    champ_t second = {0};
    data_t data = {0};
    vm_t vm;

    setup_champ(&first, 1);
    setup_champ(&second, 2);
    first.next = &second;
    setup_data(&data, &first);
    init_vm(&vm, &data);
    cr_assert_eq(vm.processes->pc, 0);
    cr_assert_eq(vm.processes->next->pc, MEM_SIZE / 2);
}

Test(init_processes, wraps_process_pc)
{
    champ_t champ = {0};
    data_t data = {0};
    vm_t vm;

    setup_champ(&champ, 1);
    champ.load_address = MEM_SIZE + 12;
    setup_data(&data, &champ);
    init_vm(&vm, &data);
    cr_assert_eq(vm.processes->pc, 12);
}
