/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** init_polltab
*/

#include "myftp.h"

void init_polltab(struct pollfd_tab_s *fds_tab)
{
    if (fds_tab == NULL)
        return;
    fds_tab->nb_fds = 0;
    fds_tab->tab_size = 10;
    fds_tab->fds_tab = malloc(sizeof(struct pollfd) * fds_tab->tab_size);
    if (fds_tab->fds_tab == NULL)
        exit(84);
}
