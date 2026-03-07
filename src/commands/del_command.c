/*
** EPITECH PROJECT, 2026
** G-NWP-400-REN-4-1-myftp-9
** File description:
** del_command
*/

#include "myftp.h"

void remove_file(struct client_s *client, char *full_path)
{
    int rm = remove(full_path);

    if (rm == 0){
        write(client->fd_client,
            "250 Requested file action okay, completed.\r\n", 44);
    } else {
        write(client->fd_client,
            "550 Requested action not taken.\r\n", 33);
    }
}

void del_command(struct client_s *client)
{
    char full_path[PATH_SIZE];

    if (client->is_logged != 1){
        write(client->fd_client, "530 Not logged in.\r\n", 20);
        return;
    }
    if (client->arg_cmd[0] == '\0'){
        write(client->fd_client,
            "501 Syntax error in parameters or arguments.\r\n", 46);
        return;
    }
    snprintf(full_path, PATH_SIZE, "%s/%s", client->current_dir,
        client->arg_cmd);
    remove_file(client, full_path);
}
