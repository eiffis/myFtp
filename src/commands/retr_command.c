/*
** EPITECH PROJECT, 2026
** G-NWP-400-REN-4-1-myftp-9
** File description:
** rtr_command
*/

#include "myftp.h"

int check_args(struct client_s *client)
{
    if (client->is_logged != 1){
        write(client->fd_client, "530 Not logged in.\r\n", 20);
        return -1;
    }
    if (client->arg_cmd[0] == '\0') {
        write(client->fd_client, "501 Syntax error in parameters.\r\n", 33);
        return -1;
    }
    return 0;
}

void retrieve_loop(int fd_file, int data_fd)
{
    char buffer[BUFFER_SZ];
    size_t bytes_read;

    bytes_read = read(fd_file, buffer, sizeof(buffer));
    while (bytes_read > 0){
        if (write(data_fd, buffer, bytes_read) == -1)
            break;
        bytes_read = read(fd_file, buffer, sizeof(buffer));
    }
}

int retrieve_file(int data_fd, struct client_s *client, int fd_file)
{
    write(client->fd_client,
        "150 File status okay; about to open data connection.\r\n", 54);
    if (fork() == 0){
        retrieve_loop(fd_file, data_fd);
        close(fd_file);
        close(data_fd);
        write(client->fd_client, "226 Closing data connection.\r\n", 30);
        exit(0);
    }
    return 0;
}

void close_all(int data_fd, struct client_s *client, int fd_file)
{
    if (retrieve_file(data_fd, client, fd_file) == -1)
        return;
    close(fd_file);
    close(data_fd);
    client->mode = -1;
}

void retr_command(struct client_s *client)
{
    int data_fd = 0;
    int fd_file;
    char full_path[PATH_SIZE];

    if (check_args(client) == -1)
        return;
    snprintf(full_path, PATH_SIZE, "%s/%s", client->current_dir,
        client->arg_cmd);
    fd_file = open(full_path, O_RDONLY);
    if (fd_file == -1){
        write(client->fd_client,
            "550 Requested action not taken. File unavailable.\r\n", 51);
        return;
    }
    data_fd = open_connection(client);
    if (data_fd == -1){
        close(fd_file);
        return;
    }
    close_all(data_fd, client, fd_file);
}
