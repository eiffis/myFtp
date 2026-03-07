/*
** EPITECH PROJECT, 2026
** G-NWP-400-REN-4-1-myftp-9
** File description:
** stor_command
*/

#include "myftp.h"

void upload_file(struct client_s *client, int data_fd)
{
    int fd_file;
    char buffer[BUFFER_SZ];
    char full_path[PATH_SIZE];
    size_t bytes_read;

    snprintf(full_path, PATH_SIZE, "%s/%s", client->current_dir,
        client->arg_cmd);
    fd_file = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd_file == -1)
        return;
    bytes_read = read(data_fd, buffer, sizeof(buffer));
    while (bytes_read > 0) {
        write(fd_file, buffer, bytes_read);
        bytes_read = read(data_fd, buffer, sizeof(buffer));
    }
    close(fd_file);
}

void core_function(struct client_s *client, int data_fd)
{
    data_fd = open_connection(client);
    if (data_fd == -1){
        write(client->fd_client, "425 Impossible to stor the file.\r\n", 34);
        return;
    }
    write(client->fd_client,
        "150 File status okay; about to open data connection.\r\n", 54);
    if (fork() == 0){
        upload_file(client, data_fd);
        close(data_fd);
        write(client->fd_client, "226 Closing data connection.\r\n", 30);
        exit(0);
    }
    close(data_fd);
    client->mode = -1;
}

void stor_command(struct client_s *client)
{
    int data_fd = -1;

    if (client->is_logged != 1){
        write(client->fd_client, "530 Not logged in.\r\n", 20);
        return;
    }
    if (client->arg_cmd[0] == '\0'){
        write(client->fd_client,
            "501 Syntax error in parameters or arguments.\r\n", 46);
        return;
    }
    core_function(client, data_fd);
}
