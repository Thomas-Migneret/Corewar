/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** main entry point
*/

#include "../include/my.h"

int malloc_struct(data_t *data)
{
    data->cycle = -1;
    data->champs = NULL;
    return 0;
}

static void free_champs(champ_t *champ)
{
    champ_t *next = NULL;

    while (champ != NULL) {
        next = champ->next;
        free(champ->path);
        free(champ->name);
        free(champ->code);
        free(champ);
        champ = next;
    }
}

static void free_processes(process_t *process)
{
    process_t *next = NULL;

    while (process != NULL) {
        next = process->next;
        free(process);
        process = next;
    }
}

static int cleanup_return(data_t *data, process_t *process, int status)
{
    free_processes(process);
    if (data != NULL) {
        free_champs(data->champs);
        free(data);
    }
    return status;
}

static int run_corewar(data_t *data)
{
    vm_t vm;

    init_vm(&vm, data);
    run_vm(&vm);
    return cleanup_return(data, vm.processes, 0);
}

int main(int argc, char **argv)
{
    data_t *data = NULL;

    if (argc < 2)
        return 84;
    if (my_strcmp(argv[1], "-h") == 0) {
        help();
        return 0;
    }
    data = malloc(sizeof(data_t));
    if (data == NULL)
        return 84;
    malloc_struct(data);
    if (recup_arg(argc, argv, data) == 84)
        return cleanup_return(data, NULL, 84);
    if (data->champs == NULL)
        return cleanup_return(data, NULL, 84);
    if (loop_open_file(data->champs, data) == NULL)
        return cleanup_return(data, NULL, 84);
    return run_corewar(data);
}
