/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** add_to_client_tab
*/

#include "myftp.h"

void add_to_client_tab(struct clients_tab_s *tab, int client_fd, struct
    server_s *server)
{
    if (tab->nb_clients >= tab->tab_size){
        tab->tab_size *= 2;
        tab->clients_tab = realloc(tab->clients_tab, sizeof(struct client_s) *
            tab->tab_size);
        if (tab->clients_tab == NULL)
            exit(84);
    }
    init_client(&tab->clients_tab[tab->nb_clients], client_fd, server);
    tab->nb_clients++;
}
