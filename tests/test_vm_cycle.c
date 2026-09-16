/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Unit tests for VM cycle scheduling
*/

#include <criterion/criterion.h>
#include "my.h"

static void setup_vm_process(vm_t *vm, process_t *process)
{
    vm->cycle = 0;
    vm->processes = process;
    process->pc = 0;
    process->wait_cycles = 0;
    process->current_opcode = 0;
    process->next = NULL;
}

Test(run_vm_cycle, increments_cycle)
{
    process_t process = {0};
    vm_t vm = {0};

    setup_vm_process(&vm, &process);
    run_vm_cycle(&vm);
    cr_assert_eq(vm.cycle, 1);
}

Test(run_vm_cycle, skips_invalid_opcode)
{
    process_t process = {0};
    vm_t vm = {0};

    setup_vm_process(&vm, &process);
    vm.arena[0] = 0xFF;
    run_vm_cycle(&vm);
    cr_assert_eq(process.pc, 1);
    cr_assert_eq(process.current_opcode, 0);
    cr_assert_eq(process.wait_cycles, 0);
}

Test(run_vm_cycle, wraps_invalid_opcode_skip)
{
    process_t process = {0};
    vm_t vm = {0};

    setup_vm_process(&vm, &process);
    process.pc = MEM_SIZE - 1;
    vm.arena[MEM_SIZE - 1] = 0xFF;
    run_vm_cycle(&vm);
    cr_assert_eq(process.pc, 0);
}

Test(run_vm_cycle, schedules_valid_opcode)
{
    process_t process = {0};
    vm_t vm = {0};

    setup_vm_process(&vm, &process);
    vm.arena[0] = 0x01;
    run_vm_cycle(&vm);
    cr_assert_eq(process.pc, 0);
    cr_assert_eq(process.current_opcode, 0x01);
    cr_assert_eq(process.wait_cycles, 10);
}

Test(run_vm_cycle, decrements_waiting_process)
{
    process_t process = {0};
    vm_t vm = {0};

    setup_vm_process(&vm, &process);
    process.current_opcode = 0x01;
    process.wait_cycles = 3;
    run_vm_cycle(&vm);
    cr_assert_eq(process.wait_cycles, 2);
    cr_assert_eq(process.current_opcode, 0x01);
}

Test(run_vm_cycle, clears_opcode_after_waiting)
{
    process_t process = {0};
    vm_t vm = {0};

    setup_vm_process(&vm, &process);
    process.current_opcode = 0x01;
    process.wait_cycles = 1;
    run_vm_cycle(&vm);
    cr_assert_eq(process.wait_cycles, 0);
    cr_assert_eq(process.current_opcode, 0);
}
