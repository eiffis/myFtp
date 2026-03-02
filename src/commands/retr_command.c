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
    size_t bytes_read;

    if (client->arg_cmd[0] == '\0')
        return;
    fd_file = open(client->arg_cmd, O_RDONLY);
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
    pid_t transfert_pid;

    if (client->is_logged != 1){
        write(client->fd_client, "530 Not logged in.\r\n", 20);
        return;
    }
    data_fd = open_connection(client);
    if (data_fd == -1)
        return;
    write(data_fd,
        "150 File status okay; about to open data connection.\r\n", 54);
    transfert_pid = fork();
    if (transfert_pid == 0)
        retrieve_file(client, data_fd);
    write(data_fd, "226 Closing data connection.\r\n", 30);
}
