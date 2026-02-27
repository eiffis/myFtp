/*
** EPITECH PROJECT, 2026
** G-NWP-400-REN-4-1-myftp-9
** File description:
** port_command
*/

#include "myftp.h"

void port_command(struct client_s *client)
{
    int p1;
    int p2;

    if (client->is_logged != 1) {
        write(client->fd_client, "530 Not logged in.\r\n", 20);
        return;
    }
    if (sscanf(client->arg_cmd, "%d,%d,%d,%d,%d,%d", &client->ip.h1,
            &client->ip.h2, &client->ip.h3, &client->ip.h4, &p1, &p2) != 6){
        write(client->fd_client,
            "501 Syntax error in parameters or arguments.\r\n", 46);
        return;
    }
    snprintf(client->data_ip, sizeof(client->data_ip), "%d.%d.%d.%d",
        client->ip.h1, client->ip.h2, client->ip.h3, client->ip.h4);
    client->data_port = (p1 * 256) + p2;
    client->mode = 1;
    write(client->fd_client, "200 Command okay.\r\n", 19);
    return;
}
