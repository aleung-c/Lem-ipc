# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/08 16:05:23 by aleung-c          #+#    #+#              #
#    Updated: 2017/06/08 16:05:24 by aleung-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = lemipc

HEADER = includes/lem-ipc.h

SRC = src/main.c \
src/lemipc.c \
src/get_game_args.c \
src/init_board.c \
src/init_display.c \
src/init_players.c \
src/board_tools.c

OBJ = $(SRC:.c=.o)

LIB = ./libft/

CC = gcc -g -Wall -Werror -Wextra -Ofast 

all : Lib $(NAME) 

$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -L./libft/ -lft -lncurses

Lib :
	make -C $(LIB)

clean :
	rm -rf $(OBJ)
	cd $(LIB) ; make clean

fclean : clean
	rm -rf $(NAME)
	cd $(LIB) ; make fclean

re : fclean all

.PHONY : all clean fclean re