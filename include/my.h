/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** Header file for the my_world function
*/

#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>

#ifndef MY_H_
    #define MY_H_
    #include "op.h"

typedef struct head_s {
    char *name;
    char *comment;
} head_t;

typedef struct body_s {
    char *label;
    char *command;
    struct body_s *next;
} body_t;

typedef struct perso_s {
    struct head_s *head;
    struct body_s *body;
} perso_t;

typedef struct info_s {
    int live;
    int add;
} info_t;

typedef struct champ_s {
    char *path;
    char *name;
    int prog_number;
    int load_address;
    int prog_size;
    unsigned char *code;
    struct champ_s *next;
} champ_t;

typedef struct process_s {
    int pc;
    int registers[REG_NUMBER];
    int carry;
    int wait_cycles;
    int current_opcode;
    int is_alive;
    int last_live_cycle;
    champ_t *champ;
    struct process_s *next;
} process_t;

typedef struct arg_s {
    int type;
    int size;
    int value;
} arg_t;

typedef struct data_s {
    int cycle;
    champ_t *champs;
} data_t;

typedef struct vm_s {
    unsigned char arena[MEM_SIZE];
    int cycle;
    int dump_cycle;
    int cycle_to_die;
    int last_death_check;
    int live_count;
    int is_finished;
    champ_t *champs;
    champ_t *last_live_champ;
    process_t *processes;
} vm_t;

void help(void);
//vm
void init_vm(vm_t *vm, data_t *data);
void dump_arena(vm_t *vm);
void set_champions_load_addresses(vm_t *vm);
void load_champions(vm_t *vm);
void init_processes(vm_t *vm);
int vm_wrap_address(int address);
unsigned char vm_read_byte(vm_t *vm, int address);
int vm_read_short(vm_t *vm, int address);
int vm_read_int(vm_t *vm, int address);
void vm_write_int(vm_t *vm, int address, int value);
void run_vm(vm_t *vm);
void run_vm_cycle(vm_t *vm);
int is_valid_register(int reg);
int get_register_value(process_t *process, int reg);
void set_register_value(process_t *process, int reg, int value);
const op_t *get_instruction_from_opcode(int opcode);
int instruction_has_coding_byte(int opcode);
int get_argument_type(unsigned char coding_byte, int index);
int get_argument_size(int opcode, int type);
int get_instruction_size(vm_t *vm, process_t *process);
int are_instruction_arguments_valid(vm_t *vm, process_t *process);
int read_instruction_args(vm_t *vm, process_t *process, arg_t *args);
void execute_instruction(vm_t *vm, process_t *process);
void execute_live(vm_t *vm, process_t *process, arg_t *args);
void execute_ld(vm_t *vm, process_t *process, arg_t *args);
void execute_lld(vm_t *vm, process_t *process, arg_t *args);
void execute_st(vm_t *vm, process_t *process, arg_t *args);
void execute_add(vm_t *vm, process_t *process, arg_t *args);
void execute_sub(vm_t *vm, process_t *process, arg_t *args);
void execute_and(vm_t *vm, process_t *process, arg_t *args);
void execute_or(vm_t *vm, process_t *process, arg_t *args);
void execute_xor(vm_t *vm, process_t *process, arg_t *args);
int execute_zjmp(vm_t *vm, process_t *process, arg_t *args);
void execute_ldi(vm_t *vm, process_t *process, arg_t *args);
void execute_sti(vm_t *vm, process_t *process, arg_t *args);
void execute_fork(vm_t *vm, process_t *process, arg_t *args);
void execute_lfork(vm_t *vm, process_t *process, arg_t *args);
void execute_lldi(vm_t *vm, process_t *process, arg_t *args);
void execute_print(vm_t *vm, process_t *process, arg_t *args);
void check_process_deaths(vm_t *vm);
void finish_vm(vm_t *vm);
//parcing
int recup_arg(int argc, char **argv, data_t *data);
//tool
int my_strcmp(const char *s1, const char *s2);
int my_getnbr(const char *str);
int my_strlen(char *str);
char *my_strncpy(char *dest, const char *src, size_t n);
//file
data_t *loop_open_file(champ_t *champ, data_t *data);

#endif /* MY_H_ */
