/*
** EPITECH PROJECT, 2026
** G-NWP-400-REN-4-1-myftp-9
** File description:
** del_command
*/

#include "myftp.h"

void del_command(struct client_s *client)
{
    int fd_file;
    int rm;

    if (client->is_logged != 1){
        write(client->fd_client, "530 Not logged in.\r\n", 20);
        return;
    }
    fd_file = open(client->arg_cmd, O_RDONLY);
    if (fd_file == -1)
        return;
    rm = remove(client->arg_cmd);
    if (rm == 0){
        write(client->fd_client,
            "250 Requested file action okay, completed.\r\n", 44);
    }
}
