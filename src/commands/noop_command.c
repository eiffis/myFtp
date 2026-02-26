/*
** EPITECH PROJECT, 2026
** G-NWP-400-REN-4-1-myftp-9
** File description:
** noop_command
*/

#include "myftp.h"

void noop_command(struct client_s *client)
{
    write(client->fd_client, "200 Command okay.\r\n", 19);
    return;
}
