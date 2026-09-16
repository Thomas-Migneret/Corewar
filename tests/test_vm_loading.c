/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Unit tests for VM champion loading
*/

#include <criterion/criterion.h>
#include "my.h"

static void setup_champ(champ_t *champ)
{
    champ->path = "test.cor";
    champ->name = "test";
    champ->prog_number = 1;
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

static void set_champ_code(champ_t *champ, unsigned char *code, int size)
{
    champ->code = code;
    champ->prog_size = size;
}

static void assert_arena_is_empty(vm_t *vm)
{
    for (int i = 0; i < MEM_SIZE; i++)
        cr_assert_eq(vm->arena[i], 0);
}

Test(init_vm, sets_initial_state)
{
    data_t data = {0};
    vm_t vm;

    setup_data(&data, NULL);
    data.cycle = 42;
    init_vm(&vm, &data);
    cr_assert_eq(vm.cycle, 0);
    cr_assert_eq(vm.dump_cycle, 42);
    cr_assert_eq(vm.cycle_to_die, CYCLE_TO_DIE);
    cr_assert_eq(vm.live_count, 0);
    cr_assert_null(vm.champs);
    cr_assert_null(vm.processes);
    assert_arena_is_empty(&vm);
}

Test(load_champions, copies_code_at_explicit_address)
{
    unsigned char code[] = {0x01, 0x02, 0x03};
    champ_t champ = {0};
    data_t data = {0};
    vm_t vm;

    setup_champ(&champ);
    set_champ_code(&champ, code, 3);
    champ.load_address = 42;
    setup_data(&data, &champ);
    init_vm(&vm, &data);
    cr_assert_eq(vm.arena[42], 0x01);
    cr_assert_eq(vm.arena[43], 0x02);
    cr_assert_eq(vm.arena[44], 0x03);
}

Test(load_champions, wraps_code_after_end_of_arena)
{
    unsigned char code[] = {0x11, 0x22, 0x33};
    champ_t champ = {0};
    data_t data = {0};
    vm_t vm;

    setup_champ(&champ);
    set_champ_code(&champ, code, 3);
    champ.load_address = MEM_SIZE - 1;
    setup_data(&data, &champ);
    init_vm(&vm, &data);
    cr_assert_eq(vm.arena[MEM_SIZE - 1], 0x11);
    cr_assert_eq(vm.arena[0], 0x22);
    cr_assert_eq(vm.arena[1], 0x33);
}

Test(load_champions, ignores_missing_code)
{
    champ_t champ = {0};
    data_t data = {0};
    vm_t vm;

    setup_champ(&champ);
    champ.load_address = 0;
    champ.prog_size = 4;
    setup_data(&data, &champ);
    init_vm(&vm, &data);
    assert_arena_is_empty(&vm);
}

Test(load_champions, spreads_missing_addresses)
{
    champ_t first = {0};
    champ_t second = {0};
    champ_t third = {0};
    data_t data = {0};
    vm_t vm;

    setup_champ(&first);
    setup_champ(&second);
    setup_champ(&third);
    first.next = &second;
    second.next = &third;
    setup_data(&data, &first);
    init_vm(&vm, &data);
    cr_assert_eq(first.load_address, 0);
    cr_assert_eq(second.load_address, MEM_SIZE / 3);
    cr_assert_eq(third.load_address, (MEM_SIZE / 3) * 2);
}

Test(load_champions, preserves_explicit_addresses)
{
    champ_t first = {0};
    champ_t second = {0};
    data_t data = {0};
    vm_t vm;

    setup_champ(&first);
    setup_champ(&second);
    first.load_address = 123;
    first.next = &second;
    setup_data(&data, &first);
    init_vm(&vm, &data);
    cr_assert_eq(first.load_address, 123);
    cr_assert_eq(second.load_address, MEM_SIZE / 2);
}
