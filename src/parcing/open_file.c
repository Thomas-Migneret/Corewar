/*
** EPITECH PROJECT, 2025
** my_world
** File description:
** main.c
*/

#include "../../include/my.h"
#include <sys/stat.h>

static int read_int_be(unsigned char *bytes)
{
    unsigned int value = 0;

    value = (unsigned int) bytes[0] << 24;
    value |= (unsigned int) bytes[1] << 16;
    value |= (unsigned int) bytes[2] << 8;
    value |= bytes[3];
    return (int) value;
}

static char *get_name(char *buffer, size_t buffer_size)
{
    unsigned char *data = (unsigned char *)buffer;
    size_t name_offset = 4;
    char *name;
    int i;

    if (buffer_size < name_offset + PROG_NAME_LENGTH)
        return NULL;
    name = malloc(sizeof(char) * (PROG_NAME_LENGTH + 1));
    if (name == NULL)
        return NULL;
    for (i = 0; i < PROG_NAME_LENGTH && data[name_offset + i] != '\0'; i++)
        name[i] = data[name_offset + i];
    name[i] = '\0';
    return name;
}

static unsigned char *get_code(char *buffer, size_t buffer_size, int *prog_size)
{
    unsigned char *data = (unsigned char *)buffer;
    size_t size_offset = 4 + (PROG_NAME_LENGTH + 1) + 3;
    size_t code_offset = size_offset + 4 + (COMMENT_LENGTH + 1) + 3;
    int size;
    unsigned char *code;

    if (buffer_size < code_offset + 1)
        return NULL;
    size = read_int_be(data + size_offset);
    if (size <= 0 || size > MEM_SIZE)
        return NULL;
    if (buffer_size < code_offset + (size_t)size)
        return NULL;
    code = malloc(sizeof(unsigned char) * size);
    if (code == NULL)
        return NULL;
    for (int i = 0; i < size; i++)
        code[i] = data[code_offset + i];
    *prog_size = size;
    return code;
}

static data_t *stockage(char *buffer, size_t buffer_size, champ_t *champ)
{
    unsigned char *data = (unsigned char *)buffer;
    int magic = read_int_be(data);
    char *name;
    unsigned char *code;

    if (magic != COREWAR_EXEC_MAGIC)
        return NULL;
    name = get_name(buffer, buffer_size);
    if (name == NULL)
        return NULL;
    code = get_code(buffer, buffer_size, &champ->prog_size);
    if (code == NULL) {
        free(name);
        return NULL;
    }
    champ->name = name;
    champ->code = code;
    return (data_t *)1;
}

static char *read_file_buffer(int fd, struct stat *st, ssize_t *size)
{
    char *buffer = malloc((size_t) st->st_size);

    if (buffer == NULL) {
        close(fd);
        return NULL;
    }
    *size = read(fd, buffer, st->st_size);
    close(fd);
    if (*size != st->st_size) {
        free(buffer);
        return NULL;
    }
    return buffer;
}

static data_t *open_file(char *filepath, champ_t *champ, data_t *data)
{
    int fd = open(filepath, O_RDONLY);
    struct stat st;
    char *buffer;
    ssize_t size;

    if (fd == -1)
        return NULL;
    if (fstat(fd, &st) == -1 || st.st_size <= 0) {
        close(fd);
        return NULL;
    }
    buffer = read_file_buffer(fd, &st, &size);
    if (buffer == NULL)
        return NULL;
    if (stockage(buffer, (size_t)size, champ) == NULL) {
        free(buffer);
        return NULL;
    }
    free(buffer);
    return data;
}

data_t *loop_open_file(champ_t *champ, data_t *data)
{
    while (champ != NULL) {
        data = open_file(champ->path, champ, data);
        if (data == NULL) {
            return NULL;
        }
        champ = champ->next;
    }
    return data;
}
