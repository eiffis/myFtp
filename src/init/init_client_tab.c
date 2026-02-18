/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** init_client_tab
*/

#include "myftp.h"

void init_client_tab(struct clients_tab_s *clients_tab)
{
    clients_tab->nb_clients = 0;
    clients_tab->tab_size = 10;
    clients_tab->clients_tab = malloc(sizeof(struct client_s) *
        clients_tab->tab_size);
    if (clients_tab->clients_tab == NULL)
        exit(84);
    for (size_t i = 0; i < clients_tab->tab_size; i++) {
        clients_tab->clients_tab[i].fd_client = -1;
        clients_tab->clients_tab[i].current_dir = NULL;
        clients_tab->clients_tab[i].is_logged = 0;
    }
}
