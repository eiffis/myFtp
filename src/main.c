/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** main
*/

#include "myftp.h"

int main(int ac, char **av)
{
    ftp_t myftp;
    int port;

    if (ac < 3)
        return 84;
    port = atoi(av[1]);
    init_ftp(&myftp, port, av[2]);
    run_ftp(&myftp);
    return 0;
}
