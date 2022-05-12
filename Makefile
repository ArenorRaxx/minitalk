# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 18:59:36 by mcorso            #+#    #+#              #
#    Updated: 2022/05/12 13:22:33 by mcorso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Name
NAME			=		minitalk
SERVER			=		server
CLIENT			=		client
BONUS			=		bonus
BSERV			=		bonus_server
BCLIE			=		bonus_client

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

#	Bonus
BONUS_SERV		=		$(addsuffix _bonus.c, $(BONUS)/$(SERVER))
OBJBO_SERV		=		$(BONUS_SERV:.c=.o)

BONUS_CLIE		=		$(addsuffix _bonus.c, $(BONUS)/$(CLIENT))
OBJBO_CLIE		=		$(BONUS_CLIE:.c=.o)

#	Compiler
CC				=		gcc
CFLAGS			=		-Wall -Werror -Wextra

#	RULES
all				:		$(NAME) $(BONUS)

$(NAME)			:		$(SERVER) $(CLIENT)

$(BONUS)		:		$(BSERV) $(BCLIE)

$(SERVER)		:		$(OBJ_SERVER)
						$(CC) $(CFLAGS) $< -o $(DIR_SERVER)/$@

$(CLIENT)		:		$(OBJ_CLIENT)
						$(CC) $(CFLAGS) $< -o $(DIR_CLIENT)/$@

$(BSERV)		:		$(OBJBO_SERV)
						$(CC) $(CFLAGS) $< -o $(BONUS)/$@

$(BCLIE)		:		$(OBJBO_CLIE)
						$(CC) $(CFLAGS) $< -o $(BONUS)/$@

.c.o			:
						$(CC) $(CFLAGS) -o $@ -c $<

clean			:
						rm -rf $(OBJ_SERVER) $(OBJ_CLIENT)
						rm -rf $(OBJBO_SERV) $(OBJBO_CLIE)

fclean			:		clean
						rm -rf $(DIR_SERVER)/$(SERVER) $(DIR_CLIENT)/$(CLIENT)
						rm -rf $(BONUS_DIR)/bonus_server $(BONUS_DIR)/bonus_client

re				:		fclean all