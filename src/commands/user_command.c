/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** user_command
*/

#include "myftp.h"

void user_command(struct client_s *client)
{
    if (client->username)
        free(client->username);
    client->username = strdup(client->arg_cmd);
    if (strcmp(client->username, "Anonymous") == 0){
        write(client->fd_client, "331 User name okay, need password.\r\n", 36);
        return;
    }
    write(client->fd_client, "501 Incorrect user.\r\n", 21);
    return;
}
