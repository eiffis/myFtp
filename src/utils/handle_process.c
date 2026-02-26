/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** handle_process
*/

#include "myftp.h"

void handle_deconnection(struct ftp_s *ftp, int i, int client_idx)
{
    close(ftp->my_fds.fds_tab[i].fd);
    ftp->my_fds.fds_tab[i].fd = -1;
    free_client(&ftp->my_clients.clients_tab[client_idx]);
    ftp->my_clients.clients_tab[client_idx].fd_client = -1;
}

void handle_events(struct ftp_s *ftp, int i)
{
    int client_idx = i;

    if (ftp->my_fds.fds_tab[i].fd == ftp->server.server_fd){
        accept_new_connection(ftp);
    } else {
        client_idx--;
        if (read_command(ftp->my_fds.fds_tab[i].fd,
                &ftp->my_clients.clients_tab[client_idx]) == -1){
            handle_deconnection(ftp, i, client_idx);
        }
    }
}

void handle_process(struct ftp_s *ftp)
{
    for (int i = 0; i < (int)ftp->my_fds.nb_fds; i++){
        if ((ftp->my_fds.fds_tab[i].revents & POLLIN) != 1)
            continue;
        handle_events(ftp, i);
    }
}
