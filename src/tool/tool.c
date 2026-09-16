/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** help file
*/

#include "my.h"

int my_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (unsigned char) *s1 - (unsigned char) *s2;
}

int my_getnbr(const char *str)
{
    int result = 0;
    int sign = 1;

    if (*str == '-') {
        sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result * sign;
}

int my_strlen(char *str)
{
    int len = 0;

    while (str[len] != '\0')
        len++;
    return len;
}

char *my_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';
    return dest;
}
