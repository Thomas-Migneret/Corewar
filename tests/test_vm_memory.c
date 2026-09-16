/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Unit tests for VM memory helpers
*/

#include <criterion/criterion.h>
#include "my.h"

Test(vm_memory, wraps_addresses)
{
    cr_assert_eq(vm_wrap_address(0), 0);
    cr_assert_eq(vm_wrap_address(MEM_SIZE), 0);
    cr_assert_eq(vm_wrap_address(MEM_SIZE + 7), 7);
    cr_assert_eq(vm_wrap_address(-1), MEM_SIZE - 1);
    cr_assert_eq(vm_wrap_address(-MEM_SIZE - 2), MEM_SIZE - 2);
}

Test(vm_memory, reads_byte_with_wrapping)
{
    vm_t vm = {0};

    vm.arena[3] = 0xAB;
    vm.arena[MEM_SIZE - 1] = 0xCD;
    cr_assert_eq(vm_read_byte(&vm, MEM_SIZE + 3), 0xAB);
    cr_assert_eq(vm_read_byte(&vm, -1), 0xCD);
}

Test(vm_memory, reads_big_endian_short)
{
    vm_t vm = {0};

    vm.arena[10] = 0x12;
    vm.arena[11] = 0x34;
    vm.arena[20] = 0xFF;
    vm.arena[21] = 0xFE;
    cr_assert_eq(vm_read_short(&vm, 10), 0x1234);
    cr_assert_eq(vm_read_short(&vm, 20), -2);
}

Test(vm_memory, reads_big_endian_int_with_wrapping)
{
    vm_t vm = {0};

    vm.arena[MEM_SIZE - 2] = 0x12;
    vm.arena[MEM_SIZE - 1] = 0x34;
    vm.arena[0] = 0x56;
    vm.arena[1] = 0x78;
    cr_assert_eq(vm_read_int(&vm, MEM_SIZE - 2), 0x12345678);
}

Test(vm_memory, writes_big_endian_int_with_wrapping)
{
    vm_t vm = {0};

    vm_write_int(&vm, MEM_SIZE - 1, 0x12345678);
    cr_assert_eq(vm.arena[MEM_SIZE - 1], 0x12);
    cr_assert_eq(vm.arena[0], 0x34);
    cr_assert_eq(vm.arena[1], 0x56);
    cr_assert_eq(vm.arena[2], 0x78);
}
