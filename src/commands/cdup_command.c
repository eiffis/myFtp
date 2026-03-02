/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** cdup_command
*/

#include "myftp.h"

void move_dir(struct client_s *client)
{
    char tmp_path[PATH_SIZE];
    char true_path[PATH_SIZE];

    strcpy(tmp_path, client->current_dir);
    strcat(tmp_path, "/..");
    if (realpath(tmp_path, true_path) == NULL){
        write(client->fd_client, "550 Requested action not taken.\r\n", 33);
        return;
    }
    if (strncmp(true_path, client->root_path, strlen(client->root_path)) != 0){
        strcpy(client->current_dir, client->root_path);
    } else
        strcpy(client->current_dir, true_path);
}

void cdup_command(struct client_s *client)
{
    if (client->is_logged != 1){
        write(client->fd_client, "530 Not logged in.\r\n", 20);
        return;
    }
    if (client->arg_cmd[0] != '\0'){
        write(client->fd_client,
            "501 Syntax error in parameters or arguments.\r\n", 46);
        return;
    }
    move_dir(client);
    write(client->fd_client, "200 Command okay.\r\n", 19);
}
