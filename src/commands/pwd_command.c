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
    char path[PATH_SIZE];

    if (client->is_logged != 1){
        write(client->fd_client, "530 Not logged in.\r\n", 20);
        return;
    }
    hidden_path = client->current_dir + strlen(client->root_path);
    if (hidden_path[0] == '\0'){
        write(client->fd_client, "257 \"/\"\r\n", 9);
    } else {
        if (hidden_path[0] != '/'){
            snprintf(path, PATH_SIZE, "257 \"/%s\"\r\n", hidden_path);
        } else {
            snprintf(path, PATH_SIZE, "257 \"%s\"\r\n", hidden_path);
        }
        write(client->fd_client, path, strlen(path));
    }
}
