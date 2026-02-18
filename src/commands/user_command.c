/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** user_command
*/

#include "myftp.h"

void user_command(struct client_s *client)
{
    printf("USER argument : %s\n", client->arg_cmd);
    client->username = strdup(client->arg_cmd);
    if (strcmp(client->username, "Anonymous") == 0){
        write(client->fd_client, "331 User name okay, need password.\r\n", 37);
        return;
    }
    write(client->fd_client, "501 Incorrect user.\r\n", 22);
    return;
}
