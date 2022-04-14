# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 18:59:36 by mcorso            #+#    #+#              #
#    Updated: 2022/04/14 09:05:21 by mcorso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Name
NAME			=		minitalk
SERVER			=		server
CLIENT			=		client
BONUS			=		bonus

#	Directories
HEAD			=		.
DIR_SERVER		=		$(HEAD)/$(SERVER)
DIR_CLIENT		=		$(HEAD)/$(CLIENT)
BONUS_DIR		=		$(HEAD)/$(BONUS)

#	Files
SRC_SERVER		=		$(addsuffix .c, $(DIR_SERVER)/$(SERVER))
OBJ_SERVER		=		$(SRC_SERVER:.c=.o)

SRC_CLIENT		=		$(addsuffix .c, $(DIR_CLIENT)/$(CLIENT))
OBJ_CLIENT		=		$(SRC_CLIENT:.c=.o)

#	Compiler
CC				=		gcc
CFLAGS			=		-Wall -Werror -Wextra

#	RULES
all				:		$(NAME)

$(NAME)			:		server client

server			:		$(OBJ_SERVER)
						$(CC) $(CFLAGS) $< -o $(DIR_SERVER)/$@

client			:		$(OBJ_CLIENT)
						$(CC) $(CFLAGS) $< -o $(DIR_CLIENT)/$@

.c.o			:
						$(CC) $(CFLAGS) -o $@ -c $<

clean			:
						-rm -rf $(OBJ_SERVER) $(OBJ_CLIENT)

fclean			:		clean
						rm -rf $(DIR_SERVER)/$(SERVER) $(DIR_CLIENT)/$(CLIENT)

re				:		fclean all