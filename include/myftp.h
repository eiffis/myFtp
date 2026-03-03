/*
** EPITECH PROJECT, 2025
** myFTP
** File description:
** myftp
*/

#ifndef INCLUDED_MYFTP_H
    #define INCLUDED_MYFTP_H
    #define PATH_SIZE 4096
    #define ARG_SIZE 4096
    #define MAX_CLIENTS 256
    #define BUFFER_SZ 4096
    #define NO_TIMEOUT -1
    #define COMMAND_TAB_SIZE 14
    #define CMD_SIZE 4096
    #define IP_SIZE 16
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <poll.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <stdio.h>
    #include <fcntl.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <sys/stat.h>

typedef struct server_s {
    int server_fd;
    struct sockaddr_in server_addr;
    int port;
    int nb_clients;
    char path[PATH_SIZE];
}server_t;

typedef struct ip_s {
    int h1;
    int h2;
    int h3;
    int h4;
}ip_t;

typedef struct client_s {
    struct ip_s ip;
    int is_logged;
    char *username;
    char *root_path;
    char *current_dir;
    char *command;
    char tmp_command[CMD_SIZE];
    char *arg_cmd;
    int fd_client;
    int mode; // 0 pour PASV : 1 pour ACTIVE
    int pasv_fd; // fd pour le pasv
    int data_port; // port pour le transfert de données
    char data_ip[IP_SIZE]; // adresse ip du client
}client_t;

typedef struct clients_tab_s {
    struct client_s *clients_tab;
    size_t nb_clients;
    size_t tab_size; // pour realloc le tab
}clients_tab_t;

typedef struct pollfd_tab_s
{
    struct pollfd *fds_tab;
    size_t nb_fds;
    size_t tab_size; // pour realloc également
}pollfd_tab_t;

typedef struct ftp_s {
    struct server_s server;
    struct clients_tab_s my_clients;
    struct pollfd_tab_s my_fds;
}ftp_t;

typedef struct command_map_s {
    char *name_cmd;
    void (*CommandFunction)(struct client_s *);
}command_map_t;

extern const command_map_t commandTab[];
void free_client(struct client_s *client);
void quit_command(struct client_s *client);
void cdup_command(struct client_s *client);
void user_command(struct client_s *client);
void pass_command(struct client_s *client);
void cwd_command(struct client_s *client);
void pasv_command(struct client_s *client);
void stor_command(struct client_s *client);
void noop_command(struct client_s *client);
void help_command(struct client_s *client);
void pwd_command(struct client_s *client);
void del_command(struct client_s *client);
void retr_command(struct client_s *client);
void port_command(struct client_s *client);
void list_command(struct client_s *client);
int init_server(struct server_s *server, int port, char *path);
void init_client(struct client_s *client, int fd, struct server_s *server);
void init_polltab(struct pollfd_tab_s *fds_tab);
void init_client_tab(struct clients_tab_s *clients_tab);
void init_ftp(struct ftp_s *ftp, int port, char *path);
int open_connection(struct client_s *client);
void add_to_fdstab(struct pollfd_tab_s *tab, int fd, short event);
void add_to_client_tab(struct clients_tab_s *tab, int client_fd,
    struct server_s *server);
void accept_new_connection(struct ftp_s *ftp);
void handle_process(struct ftp_s *ftp);
int read_command(int fd, struct client_s *client);
int run_ftp(struct ftp_s *ftp);


#endif

/* -------------------------------------------------------------------------- **
**                                                                            **
** MIT License                                                                **
** Copyright (c) 2025 Anonymous                                               **
**                                                                            **
** Permission is hereby granted, free of charge, to any person obtaining a    **
** copy of this software and associated documentation files (the "Software"), **
** to deal in the Software without restriction, including without limitation  **
** the rights to use, copy, modify, merge, publish, distribute, sublicense,   **
** and/or sell copies of the Software, and to permit persons to whom the      **
** Software is furnished to do so, subject to the following conditions:       **
**                                                                            **
** The above copyright notice and this permission notice shall be included in **
** all copies or substantial portions of the Software.                        **
**                                                                            **
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR **
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   **
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    **
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER **
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    **
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        **
** DEALINGS IN THE SOFTWARE.                                                  **
**                                                                            **
** -------------------------------------------------------------------------- */
