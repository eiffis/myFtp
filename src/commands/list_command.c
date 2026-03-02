/*
** EPITECH PROJECT, 2026
** G-NWP-400-REN-4-1-myftp-9
** File description:
** list_command
*/

#include "myftp.h"

void list_directory(int data_fd)
{
    FILE *fp;
    char path[PATH_SIZE];

    fp = popen("ls -l", "r");
    if (fp == NULL)
        return;
    while (fgets(path, PATH_SIZE, fp) != NULL){
        path[strlen(path)] = '\0';
        write(data_fd, path, strlen(path));
        write(data_fd, "\r\n", 1);
    }
}

void list_command(struct client_s *client)
{
    int data_fd;

    if (client->is_logged != 1){
        write(client->fd_client, "530 Not logged in.\r\n", 20);
        return;
    }
    data_fd = open_connection(client);
    if (data_fd == -1)
        return;
    write(data_fd,
        "150 File status okay; about to open data connection.\r\n", 54);
    list_directory(data_fd);
    write(data_fd, "226 Closing data connection.\r\n", 30);
}
