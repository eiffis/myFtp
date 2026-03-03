/*
** EPITECH PROJECT, 2026
** G-NWP-400-REN-4-1-myftp-9
** File description:
** stor_command
*/

#include "myftp.h"

void upload_file(struct client_s *client, int data_fd)
{
    FILE *fptr;
    char buffer[BUFFER_SZ];
    size_t bytes_read;

    if (client->arg_cmd[0] == '\0')
        return;
    bytes_read = read(data_fd, buffer, sizeof(buffer));
    buffer[bytes_read] = '\0';
    fptr = fopen(client->arg_cmd, "w");
    fprintf(fptr, "%s", buffer);
    fclose(fptr);
}

void stor_command(struct client_s *client)
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
        upload_file(client, data_fd);
    write(data_fd, "226 Closing data connection.\r\n", 30);
}
