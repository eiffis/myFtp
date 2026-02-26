/*
** EPITECH PROJECT, 2026
** G-NWP-400-REN-4-1-myftp-9
** File description:
** help_command
*/

#include "myftp.h"

void help_command(struct client_s *client)
{
    write(client->fd_client, "214 Help message.\r\n", 19);
    return;
}
