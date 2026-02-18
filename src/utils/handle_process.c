/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** handle_process
*/

#include "myftp.h"

void handle_process(struct ftp_s *ftp)
{
    int client_idx;

    for (int i = 0; i < (int)ftp->my_fds.nb_fds; i++){
        if ((ftp->my_fds.fds_tab[i].revents & POLLIN) != 1)
            continue;
        if (ftp->my_fds.fds_tab[i].fd == ftp->server.server_fd){
            accept_new_connection(ftp);
        } else {
            client_idx = i;
            client_idx--;
            read_command(ftp->my_fds.fds_tab[i].fd,
                &ftp->my_clients.clients_tab[client_idx]);
        }
    }
}
