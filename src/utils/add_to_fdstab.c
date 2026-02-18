/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** add_to_fdstab
*/

#include "myftp.h"

void add_to_fdstab(struct pollfd_tab_s *tab, int fd, short event)
{
    if (tab->nb_fds >= tab->tab_size){
        tab->tab_size *= 2;
        tab->fds_tab = realloc(tab->fds_tab, sizeof(struct pollfd) *
            tab->tab_size);
        if (tab->fds_tab == NULL)
            exit(84);
    }
    tab->fds_tab[tab->nb_fds].fd = fd;
    tab->fds_tab[tab->nb_fds].events = event;
    tab->fds_tab[tab->nb_fds].revents = 0;
    tab->nb_fds++;
}
