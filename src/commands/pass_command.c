/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** pass_command
*/

#include "myftp.h"

void pass_command(struct client_s *client)
{
    if (client->username == NULL){
        write(client->fd_client, "332 Need account for login.\r\n", 29);
        return;
    }
    if (client->arg_cmd[0] == '\0' && strcmp(client->username,
            "Anonymous") == 0){
        client->is_logged = 1;
        write(client->fd_client, "230 User logged in, proceed.\r\n", 30);
        return;
    }
    write(client->fd_client, "530 Login incorrect.\r\n", 22);
    return;
}
