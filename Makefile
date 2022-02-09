# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 18:59:36 by mcorso            #+#    #+#              #
#    Updated: 2022/02/09 11:30:37 by mcorso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	dir
BON_DIR			=		./bonus

#	server
SERVER_SRCS		=		server.c
SERVER_OBJS		=		$(SERVER_SRCS:.c=.o)
SERVER_NAME		=		server

#	client
CLIENT_SRCS		=		client.c
CLIENT_OBJS		=		$(CLIENT_SRCS:.c=.o)
CLIENT_NAME		=		client

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

all				:		$(NAME)

clean			:
						rm -rf $(SERVER_OBJS) $(CLIENT_OBJS)

fclean			:		clean
						rm -rf $(SERVER_NAME) $(CLIENT_NAME)

re				:		fclean all

.PHONY			:		all clean fclean re bonus