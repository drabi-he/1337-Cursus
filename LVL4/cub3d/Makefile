# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 22:05:25 by hdrabi            #+#    #+#              #
#    Updated: 2022/04/13 13:55:22 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = parsing/parsing_utils_five.c \
		parsing/parsing_utils_four.c \
		parsing/parsing_utils_one.c \
		parsing/parsing_utils_six.c \
		parsing/parsing_utils_three.c \
		parsing/parsing_utils_two.c \
		parsing/parsing_utils_seven.c \
		parsing/main_parse.c \
		utils/utils.c \
		utils/utils2.c \
		init/init.c \
		init/dda.c \
		graphic/mini_utils.c \
		graphic/mini_utils2.c \
		graphic/draw_screen.c \
		graphic/sprite.c \
		graphic/sprite2.c \
		keypress/key_press.c \
		keypress/key_press2.c \
		keypress/mouse_move.c


SRCM = mandatory.c

SRCB = bonus.c

NAME = cub3D

BNAME = haha

CFLAGS = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME): $(SRC) cub3d.h
	$(CC) $(CFLAGS) $(SRCM) $(SRC) -o $(NAME)

bonus : $(BNAME)

$(BNAME): $(SRC) cub3d.h
	$(CC) $(CFLAGS) $(SRCB) $(SRC) -o $(BNAME)

clean:
	rm -rf $(NAME)
	rm -rf $(BNAME)

fclean: clean

re: fclean all

run : re
	clear && ./cub3d bonus.cub