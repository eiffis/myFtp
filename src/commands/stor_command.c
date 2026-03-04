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
    char full_path[PATH_SIZE];
    size_t bytes_read;

    if (client->arg_cmd[0] != '\0'){
        write(client->fd_client,
            "501 Syntax error in parameters or arguments.\r\n", 46);
        return;
    }
    snprintf(full_path, PATH_SIZE, "%s/%s", client->current_dir,
        client->arg_cmd);
    bytes_read = read(data_fd, buffer, sizeof(buffer));
    buffer[bytes_read] = '\0';
    fptr = fopen(full_path, "w");
    fprintf(fptr, "%s", buffer);
    fclose(fptr);
}

void stor_command(struct client_s *client)
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
        upload_file(client, data_fd);
        close(data_fd);
        write(client->fd_client, "226 Closing data connection.\r\n", 30);
        exit(0);
    }
    close(data_fd);
    client->mode = -1;
}
