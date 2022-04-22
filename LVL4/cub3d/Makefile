# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 22:05:25 by hdrabi            #+#    #+#              #
#    Updated: 2022/04/22 14:35:40 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = parsing/mini_utils.c \
		parsing/mini_utils2.c \
		parsing/utils.c \
		parsing/utils2.c \
		parsing/utils3.c \
		parsing/parse_map.c \
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

BNAME = cub3D_bonus

CFLAGS = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(SRCM) $(SRC) cub3d.h
	$(CC) $(CFLAGS) $(SRCM) $(SRC) -o $(NAME)

bonus: $(BNAME)

$(BNAME): $(SRCB) $(SRC) cub3d.h
	$(CC) $(CFLAGS) $(SRCB) $(SRC) -o $(BNAME)

clean:
	rm -rf $(NAME)
	rm -rf $(BNAME)

fclean: clean

re: fclean all

run_m: all
	./cub3D maps/man.cub

run_b: bonus
	./cub3D_bonus maps/bonus.cub
	exit

.PHONY: bonus all re clean fclean