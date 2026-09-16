/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** main entry point
*/

#include "../../include/my.h"

int is_cor(char *str)
{
    int len = my_strlen(str);

    if (len < 4)
        return 0;
    return my_strcmp(str + len - 4, ".cor") == 0;
}

static char *copy_string(char *str)
{
    int len = my_strlen(str);
    char *copy = malloc(sizeof(char) * (len + 1));

    if (copy == NULL)
        return NULL;
    for (int i = 0; i < len; i++)
        copy[i] = str[i];
    copy[len] = '\0';
    return copy;
}

static void add_champ(char *name, int n, int a, data_t *data)
{
    champ_t *champ = malloc(sizeof(champ_t));
    champ_t **current = &data->champs;

    champ->path = copy_string(name);
    champ->name = NULL;
    champ->prog_number = n;
    champ->load_address = a;
    champ->prog_size = 0;
    champ->code = NULL;
    champ->next = NULL;
    while (*current != NULL)
        current = &(*current)->next;
    *current = champ;
}

static int is_unsigned_number(char *str)
{
    if (str[0] == '\0')
        return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

static int read_dump(int argc, char **argv, int i, data_t *data)
{
    if (my_strcmp(argv[i], "-dump") != 0)
        return 0;
    if (i + 1 >= argc || !is_unsigned_number(argv[i + 1]))
        return 84;
    data->cycle = my_getnbr(argv[i + 1]);
    return 0;
}

static int read_prog_number(int argc, char **argv, int i, int *n)
{
    if (my_strcmp(argv[i], "-n") != 0)
        return 0;
    if (i + 1 >= argc || !is_unsigned_number(argv[i + 1]))
        return 84;
    *n = my_getnbr(argv[i + 1]);
    return 0;
}

static int read_load_address(int argc, char **argv, int i, int *a)
{
    if (my_strcmp(argv[i], "-a") != 0)
        return 0;
    if (i + 1 >= argc || !is_unsigned_number(argv[i + 1]))
        return 84;
    *a = my_getnbr(argv[i + 1]);
    return 0;
}

static int is_prog_number_used(champ_t *champs, int prog_number)
{
    for (champ_t *champ = champs; champ != NULL; champ = champ->next) {
        if (champ->prog_number == prog_number)
            return 1;
    }
    return 0;
}

static void set_default_prog_numbers(champ_t *champs, int *prog_number)
{
    for (champ_t *champ = champs; champ != NULL; champ = champ->next) {
        if (champ->prog_number != -1)
            continue;
        while (is_prog_number_used(champs, *prog_number))
            (*prog_number)++;
        champ->prog_number = *prog_number;
    }
}

int recup_arg(int argc, char **argv, data_t *data)
{
    int n = -1;
    int a = -1;
    int prog_number = 1;

    for (int i = 1; i < argc; i++) {
        if (read_dump(argc, argv, i, data) == 84 ||
            read_prog_number(argc, argv, i, &n) == 84 ||
            read_load_address(argc, argv, i, &a) == 84)
            return 84;
        if (is_cor(argv[i])) {
            add_champ(argv[i], n, a, data);
            n = -1;
            a = -1;
        }
    }
    set_default_prog_numbers(data->champs, &prog_number);
    return 0;
}
