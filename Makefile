##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

NAME    =   myftp

CC      =   epiclang

## Main
SRC     =   main.c
SRC    +=	src/run_ftp.c

## Initialisation
SRC    +=	src/init/init_client_tab.c
SRC    +=	src/init/init_client.c
SRC    +=	src/init/init_server.c
SRC    +=	src/init/init_polltab.c
SRC    +=	src/init/init_ftp.c

## Utils
SRC	   +=	src/utils/add_to_fdstab.c
SRC	   +=	src/utils/add_to_client_tab.c
SRC    +=	src/utils/accept_new_connection.c
SRC	   +=	src/utils/handle_process.c
SRC	   +=	src/utils/read_command.c

## Commands
SRC    +=	src/commands/pass_command.c
SRC    +=	src/commands/user_command.c
SRC	   +=	src/commands/commands_tab.c
SRC	   +=   src/commands/cwd_command.c
SRC    +=   src/commands/pwd_command.c
SRC    +=   src/commands/cdup_command.c
SRC    +=   src/commands/quit_command.c
SRC    +=   src/commands/help_command.c
SRC    +=   src/commands/noop_command.c
SRC    +=   src/commands/pasv_command.c
SRC    +=   src/commands/port_command.c
SRC    +=   src/commands/list_command.c
SRC    +=   src/commands/retr_command.c
SRC    +=   src/commands/del_command.c
SRC    +=   src/commands/stor_command.c
SRC    +=   src/commands/type_command.c

## Data transfert
SRC    +=   src/data/open_connection.c

OBJ     =   $(SRC:.c=.o)

CFLAGS  =   -I./include/ -Wall -Wextra -g

all:    $(NAME)

$(NAME):    $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

%.o:    %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:     fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug