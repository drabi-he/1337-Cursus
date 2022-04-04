# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 10:11:47 by hdrabi            #+#    #+#              #
#    Updated: 2022/04/04 13:41:49 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = utils/error_handle.c \
		utils/mini_utils.c \
		utils/mini_utils2.c \
		parsing/read_map.c \
		parsing/verify_walls.c \
		raycasting/init.c \
		raycasting/mini_map.c \
		raycasting/draw_screen.c \
		raycasting/key_press.c \
		raycasting/gameplay.c \
		cub3d.c

NAME = cub3d

#CFLAGS = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

run : re
	clear && ./cub3d map.cub
