/*
** EPITECH PROJECT, 2026
** myFTP
** File description:
** read_command
*/

#include "myftp.h"

static void execute_command(struct client_s *client)
{
    for (int i = 0; i < COMMAND_TAB_SIZE; i++){
        if (strcmp(client->command, commandTab[i].name_cmd) == 0){
            commandTab[i].CommandFunction(client);
            client->command[0] = '\0';
            return;
        }
    }
    write(client->fd_client, "500 Syntax error, command unrecognized.\r\n", 41);
    return;
}

static void free_utils(char *token, char *cmd_to_split)
{
    free(token);
    free(cmd_to_split);
}

static void get_cmd_arg(char *cmd, struct client_s *client)
{
    char *cmd_to_split = strdup(cmd);
    char *token = NULL;
    char *command = NULL;
    char *arg = NULL;

    token = strtok(cmd_to_split, " ");
    for (int i = 0; token != NULL; i++){
        if (i == 0)
            command = token;
        if (i == 1)
            arg = token;
        token = strtok(NULL, " ");
    }
    if (command)
        client->command = strdup(command);
    if (!arg)
        client->arg_cmd = strdup("");
    else client->arg_cmd = strdup(arg);
    execute_command(client);
    free_utils(token, cmd_to_split);
}

static void parse_command(struct client_s *client)
{
    char *start = strdup(client->tmp_command);
    char *save_start = start;
    char *end;

    end = strstr(start, "\r\n");
    while (end != NULL){
        *end = '\0';
        get_cmd_arg(start, client);
        start = end + 2;
        end = strstr(start, "\r\n");
    }
    strcpy(client->tmp_command, start);
    free(save_start);
    return;
}

static void detect_crlf(char *buffer, struct client_s *client)
{
    char *find;

    strcat(client->tmp_command, buffer);
    find = strstr(client->tmp_command, "\r\n");
    if (find){
        parse_command(client);
        return;
    }
    return;
}

int read_command(int fd, struct client_s *client)
{
    char buffer[CMD_SIZE];
    ssize_t bytes_read;

    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1)
        return 0;
    if (bytes_read == 0){
        close(client->fd_client);
        return -1;
    }
    buffer[bytes_read] = '\0';
    if (strlen(buffer) > 0)
        detect_crlf(buffer, client);
    return 0;
}
