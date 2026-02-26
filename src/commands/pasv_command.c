/*
** EPITECH PROJECT, 2026
** G-NWP-400-REN-4-1-myftp-9
** File description:
** pasv_command
*/

#include "myftp.h"

void fill_data_pasv_addr(struct sockaddr_in *pasv_addr)
{
    memset(&pasv_addr, 0, sizeof(pasv_addr));
    pasv_addr->sin_family = AF_INET;
    pasv_addr->sin_port = htons(0);
    pasv_addr->sin_addr.s_addr = htonl(INADDR_ANY);
}

int create_data_socket(struct client_s *client, struct sockaddr_in *pasv_addr)
{
    socklen_t pasv_len = sizeof(struct sockaddr_in);

    client->pasv_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->pasv_fd == -1)
        return -1;
    fill_data_pasv_addr(pasv_addr);
    if (bind(client->pasv_fd, (struct sockaddr *)pasv_addr,
            sizeof(pasv_addr)) < 0){
        close(client->pasv_fd);
        return -1;
    }
    if (listen(client->pasv_fd, 1) < 0){
        close(client->pasv_fd);
        return -1;
    }
    if (getsockname(client->pasv_fd,
            (struct sockaddr *)pasv_addr, &pasv_len) < 0){
        close(client->pasv_fd);
        return -1;
    }
    return 0;
}

void pasv_command(struct client_s *client)
{
    struct sockaddr_in pasv_addr;
    char buffer[256];

    if (client->is_logged != 1) {
        write(client->fd_client, "530 Not logged in.\r\n", 20);
        return;
    }
    if (create_data_socket(client, &pasv_addr) < 0) {
        write(client->fd_client, "425 Can't open data connection.\r\n", 33);
        return;
    }
    client->data_port = ntohs(pasv_addr.sin_port);
    client->mode = 0;
    snprintf(buffer, sizeof(buffer),
        "227 Entering Passive Mode (127.0.0.1, %d, %d).\r\n",
        client->data_port / 256, client->data_port % 256);
    write(client->fd_client, &buffer, strlen(buffer));
    return;
}
