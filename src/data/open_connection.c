/*
** EPITECH PROJECT, 2026
** G-NWP-400-REN-4-1-myftp-9
** File description:
** open_connection
*/

#include "myftp.h"

int open_connection(struct client_s *client)
{
    int port_socket;
    struct sockaddr_in socket_addr;
    socklen_t socket_len = sizeof(struct sockaddr_in);
    int data_fd = -1;

    if (client->mode == 0) {
        data_fd = accept(client->pasv_fd, NULL, NULL);
        close(client->pasv_fd);
    } else if (client->mode == 1) {
        port_socket = socket(AF_INET, SOCK_STREAM, 0);
        socket_addr.sin_family = AF_INET;
        socket_addr.sin_port = htons(client->data_port);
        socket_addr.sin_addr.s_addr = htonl(atoi(client->data_ip));
        data_fd = connect(port_socket,
            (struct sockaddr *)&socket_addr, socket_len);
    }
    return data_fd;
}
