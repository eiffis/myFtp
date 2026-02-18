/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** init_server
*/

#include "myftp.h"

int get_path(struct server_s *server, char *path)
{
    if (realpath(path, server->path) == NULL)
        return 84;
    return 0;
}

int init_server(struct server_s *server, int port, char *path)
{
    server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->server_fd == -1)
        return -1;
    if (setsockopt(server->server_fd, SOL_SOCKET,
            SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
        return -1;
    server->port = port;
    if (get_path(server, path) == 84)
        return -1;
    server->nb_clients = 0;
    memset(&server->server_addr, 0, sizeof(server->server_addr));
    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_port = htons(port);
    server->server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server->server_fd, (struct sockaddr *)&server->server_addr,
            sizeof(server->server_addr)) < 0)
        return -1;
    if (listen(server->server_fd, SOMAXCONN) < 0)
        return -1;
    return 0;
}
