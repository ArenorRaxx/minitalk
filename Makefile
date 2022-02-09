# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 18:59:36 by mcorso            #+#    #+#              #
#    Updated: 2022/02/09 18:44:28 by mcorso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	dir
BON_DIR			=		./bonus

#	server
SERVER_SRCS		=		server.c
SERVER_OBJS		=		$(SERVER_SRCS:.c=.o)
SERVER_NAME		=		server

SERVER_BONUS	=		./bonus/server_bonus.c
SERVER_BOBJS	=		$(SERVER_BONUS:.c=.o)
SERVER_BNAME	=		server_bonus

#	client
CLIENT_SRCS		=		client.c
CLIENT_OBJS		=		$(CLIENT_SRCS:.c=.o)
CLIENT_NAME		=		client

CLIENT_BONUS	=		./bonus/client_bonus.c
CLIENT_BOBJS	=		$(CLIENT_BONUS:.c=.o)
CLIENT_BNAME	=		client_bonus

#	compiler
NAME			=		minitalk
CC				=		gcc
CFLAGS			=		-Wall -Werror -Wextra

#	rules
$(NAME)			:		$(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME)	:		$(SERVER_OBJS)
						$(CC) $(CFLAGS) $^ -o $@

$(CLIENT_NAME)	:		$(CLIENT_OBJS)
						$(CC) $(CFLAGS) $^ -o $@

$(SERVER_BNAME)	:		$(SERVER_BOBJS)
						$(CC) $(CFLAGS) $^ -o $@

$(CLIENT_BNAME)	:		$(CLIENT_BOBJS)
						$(CC) $(CFLAGS) $^ -o $@

all				:		$(NAME) bonus

clean			:
						rm -rf $(SERVER_OBJS) $(CLIENT_OBJS)

fclean			:		clean
						rm -rf $(SERVER_NAME) $(CLIENT_NAME)

re				:		fclean all

bonus			:		$(SERVER_BNAME) $(CLIENT_BNAME)

.PHONY			:		all clean fclean re bonus