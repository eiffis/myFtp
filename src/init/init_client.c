/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** init_client
*/

#include "myftp.h"

void init_client(struct client_s *client, int fd, struct server_s *server)
{
    if (client == NULL || server == NULL)
        return;
    client->current_dir = strdup(server->path);
    client->fd_client = fd;
    client->root_path = strdup(server->path);
    client->is_logged = 0;
    client->username = NULL;
    client->command = NULL;
    client->arg_cmd = NULL;
    client->tmp_command[0] = '\0';
    client->pasv_fd = -1;
    client->mode = -1;
}
