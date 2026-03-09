/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** commands_tab
*/

#include "myftp.h"

const command_map_t commandTab[] = {
    {"USER", &user_command},
    {"PASS", &pass_command},
    {"CWD", &cwd_command},
    {"PWD", &pwd_command},
    {"CDUP", &cdup_command},
    {"QUIT", &quit_command},
    {"HELP", &help_command},
    {"NOOP", &noop_command},
    {"PASV", &pasv_command},
    {"PORT", &port_command},
    {"LIST", &list_command},
    {"RETR", &retr_command},
    {"DELE", &del_command},
    {"STOR", &stor_command},
    {"TYPE", &type_command}
};
