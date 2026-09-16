/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** help file
*/

#include "my.h"

static void write_text(char *text)
{
    write(1, text, my_strlen(text));
}

void help(void)
{
    write_text("USAGE\n");
    write_text("./corewar [-dump nbr_cycle] [[-n prog_number] ");
    write_text("[-a load_address] prog_name] ...\n");
    write_text("DESCRIPTION\n");
    write_text("-dump nbr_cycle dumps the state of the virtual ");
    write_text("machine after the nbr_cycle execution\n");
    write_text("-n prog_number sets the next program's number. ");
    write_text("By default, the first free number in the parameter order\n");
    write_text("-a load_address sets the next program's loading address. ");
    write_text("When no address is specified, optimize the address ");
    write_text("so that the processes are as far away ");
    write_text("from each other as possible. ");
    write_text("The addresses are MEM_SIZE modulo.\n");
}
