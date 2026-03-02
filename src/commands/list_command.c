/*
** EPITECH PROJECT, 2026
** G-NWP-400-REN-4-1-myftp-9
** File description:
** list_command
*/

#include "myftp.h"

void list_command(struct client_s *client)
{
    char *path;
    pid_t transfert_pid;
    int data_fd;

    if (!client->arg_cmd)
        path = strdup(".");
    else
        path = strdup(client->arg_cmd);
    if (client->is_logged != 1){
        write(client->fd_client, "530 Not logged in.\r\n", 20);
    }
    data_fd = open_connection(client);
    if (data_fd == -1)
        return;
    write(data_fd,
        "150 File status okay; about to open data connection.\r\n", 54);
    transfert_pid = fork();
    if (transfert_pid == 0)
        execlp("/bin/ls", path);
    write(data_fd, "226 Closing data connection.\r\n", 30);
}
