/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** pwd_command
*/

#include "myftp.h"

void pwd_command(struct client_s *client)
{
    char *hidden_path;

    if (client->is_logged != 1){
        write(client->fd_client, "530 Not logged in.\r\n", 20);
        return;
    }
    hidden_path = client->current_dir + strlen(client->root_path);
    if (hidden_path[0] == '\0'){
        write(client->fd_client, "/\r\n", 3);
    } else {
        if (hidden_path[0] != '/'){
            write(client->fd_client, "/", 1);
            write(client->fd_client, hidden_path, strlen(hidden_path));
            write(client->fd_client, "\r\n", 2);
        } else {
            write(client->fd_client, "257 ", 4);
            write(client->fd_client, hidden_path, strlen(hidden_path));
        }
    }
}
