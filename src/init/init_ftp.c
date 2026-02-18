/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** init_ftp
*/

#include "myftp.h"

void init_ftp(struct ftp_s *ftp, int port, char *path)
{
    if (ftp == NULL)
        return;
    if (init_server(&ftp->server, port, path) != 0)
        exit(84);
    init_client_tab(&ftp->my_clients);
    init_polltab(&ftp->my_fds);
    add_to_fdstab(&ftp->my_fds, ftp->server.server_fd, POLLIN);
}
