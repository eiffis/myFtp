/*
** EPITECH PROJECT, 2026
** G-NWP-400-REN-4-1-myftp-9
** File description:
** type_command
*/

#include "myftp.h"

void type_command(struct client_s *client)
{
    write(client->fd_client, "200 Command okay.\r\n", 19);
}
