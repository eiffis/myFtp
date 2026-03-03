/*
** EPITECH PROJECT, 2026
** G-NWP-400-REN-4-1-myftp-9
** File description:
** open_connection
*/

#include "myftp.h"

int open_connection(struct client_s *client)
{
    struct sockaddr_in socket_addr;
    socklen_t sock_len = sizeof(struct sockaddr_in);
    int data_fd = -1;

    if (client->mode == 0 && client->pasv_fd != -1) {
        data_fd = accept(client->pasv_fd, NULL, NULL);
        close(client->pasv_fd);
        client->pasv_fd = -1;
    } else if (client->mode == 1) {
        data_fd = socket(AF_INET, SOCK_STREAM, 0);
        socket_addr.sin_family = AF_INET;
        socket_addr.sin_port = htons(client->data_port);
        socket_addr.sin_addr.s_addr = inet_addr(client->data_ip);
        connect(data_fd, (struct sockaddr *)&socket_addr, sock_len);
    }
    return data_fd;
}
