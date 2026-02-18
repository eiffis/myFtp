/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** run_ftp
*/

#include "myftp.h"



int run_ftp(struct ftp_s *ftp)
{
    while (1){
        if (poll(ftp->my_fds.fds_tab, ftp->my_fds.nb_fds, NO_TIMEOUT) == -1)
            break;
        handle_process(ftp);
    }
    return 0;
}
