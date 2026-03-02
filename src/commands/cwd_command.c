/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** cwd_command
*/

#include "myftp.h"

char *valid_path(struct client_s *client)
{
    char temp_path[PATH_SIZE];
    char *real = malloc(sizeof(char) * PATH_SIZE);

    if (!real)
        return NULL;
    if (client->arg_cmd[0] == '/')
        snprintf(temp_path, PATH_SIZE, "%s/%s", client->root_path,
            client->arg_cmd);
    else {
        snprintf(temp_path, PATH_SIZE, "%s/%s",
            client->current_dir, client->arg_cmd);
    }
    if (realpath(temp_path, real) == NULL ||
        strncmp(real, client->root_path, strlen(client->root_path)) != 0) {
        return NULL;
    }
    return real;
}

void cwd_command(struct client_s *client)
{
    char *real;

    if (client->is_logged != 1){
        write(client->fd_client, "530 Not logged in.\r\n", 20);
        return;
    }
    if (client->arg_cmd[0] == '\0'){
        write(client->fd_client,
            "501 Syntax error in parameters or arguments.\r\n", 46);
        return;
    }
    real = valid_path(client);
    if (real != NULL){
        free(client->current_dir);
        client->current_dir = real;
        client->current_dir = real;
        write(client->fd_client,
            "250 Requested file action okay, completed.\r\n", 44);
    } else
        write(client->fd_client, "550 Requested action not taken.\r\n", 33);
}
