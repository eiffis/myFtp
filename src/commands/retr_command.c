/*
** EPITECH PROJECT, 2026
** G-NWP-400-REN-4-1-myftp-9
** File description:
** rtr_command
*/

#include "myftp.h"

void retrieve_file(struct client_s *client, int data_fd)
{
    int fd_file;
    char buffer[BUFFER_SZ];
    char full_path[PATH_SIZE];
    size_t bytes_read;

    if (client->arg_cmd[0] == '\0')
        return;
    snprintf(full_path, PATH_SIZE, "%s/%s", client->current_dir,
        client->arg_cmd);
    fd_file = open(full_path, O_RDONLY);
    if (fd_file == -1)
        return;
    bytes_read = read(fd_file, buffer, sizeof(buffer));
    while (bytes_read > 0){
        if (write(data_fd, buffer, bytes_read) == -1)
            break;
        bytes_read = read(fd_file, buffer, sizeof(buffer));
    }
    close(fd_file);
}

void retr_command(struct client_s *client)
{
    int data_fd;

    if (client->is_logged != 1){
        write(client->fd_client, "530 Not logged in.\r\n", 20);
        return;
    }
    data_fd = open_connection(client);
    if (data_fd == -1)
        return;
    write(client->fd_client,
        "150 File status okay; about to open data connection.\r\n", 54);
    if (fork() == 0){
        retrieve_file(client, data_fd);
        close(data_fd);
        exit(0);
    }
    close(data_fd);
    client->mode = -1;
    write(client->fd_client, "226 Closing data connection.\r\n", 30);
}
