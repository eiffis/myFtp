/*
** EPITECH PROJECT, 2026
** G-NWP-400-REN-4-1-myftp-9
** File description:
** open_connection
*/

#include "myftp.h"

int open_connection(struct client_s *client)
{
    int data_fd = -1;

    if (client->mode == 0) { // MODE PASV
        data_fd = accept(client->pasv_fd, NULL, NULL);
    } else if (client->mode == 1) { // Mode active
        return data_fd;
    }
    return data_fd;
}
