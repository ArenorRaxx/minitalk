# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcorso <mcorso@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 18:59:36 by mcorso            #+#    #+#              #
#    Updated: 2022/04/15 19:26:41 by mcorso           ###   ########.fr        #
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

#	Bonus
BONUS_SERV		=		$(addprefix $(BONUS)/, $(SERVER)_bonus.c)
OBJBO_SERV		=		$(BONUS_SERV:.c=.o)

BONUS_CLIE		=		$(addprefix $(BONUS)/, $(CLIENT)_bonus.c)
OBJBO_CLIE		=		$(BONUS_CLIE:.c=.o)

#	Compiler
CC				=		gcc
CFLAGS			=		-Wall -Werror -Wextra

#	RULES
all				:		$(NAME) bonus

$(NAME)			:		server client

bonus			:		bonus_server bonus_client

server			:		$(OBJ_SERVER)
						$(CC) $(CFLAGS) $< -o $(DIR_SERVER)/$@

client			:		$(OBJ_CLIENT)
						$(CC) $(CFLAGS) $< -o $(DIR_CLIENT)/$@

bonus_server	:		$(OBJBO_SERV)
						$(CC) $(CFLAGS) $< -o $(BONUS)/$@

bonus_client	:		$(OBJBO_CLIE)
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