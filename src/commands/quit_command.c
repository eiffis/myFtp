/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** quit_command
*/

#include "myftp.h"

void free_client(struct client_s *client)
{
    if (client->arg_cmd)
        free(client->arg_cmd);
    if (client->command)
        free(client->command);
    free(client->current_dir);
    client->is_logged = 0;
    if (client->root_path)
        free(client->root_path);
    if (client->tmp_command[0] != '\0')
        client->tmp_command[0] = '\0';
    if (client->username)
        free(client->username);
    close(client->fd_client);
}

void quit_command(struct client_s *client)
{
    if (client->is_logged != 1){
        write(client->fd_client, "530 Not logged in.\r\n", 20);
        return;
    }
    write(client->fd_client, "221 Service closing control connection\r\n", 40);
    free_client(client);
}
