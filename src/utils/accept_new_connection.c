/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** accept_new_connection
*/

#include "myftp.h"

void accept_new_connection(struct ftp_s *ftp)
{
    int new_client;

    new_client = accept(ftp->server.server_fd, NULL, NULL);
    if (new_client < 0)
        return;
    add_to_fdstab(&ftp->my_fds, new_client, POLLIN);
    add_to_client_tab(&ftp->my_clients, new_client, &ftp->server);
    write(new_client, "220 Service ready for new user.\r\n", 33);
}
