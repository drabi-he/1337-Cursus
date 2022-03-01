# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 11:27:12 by hdrabi            #+#    #+#              #
#    Updated: 2022/02/28 10:43:17 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCM = mandatory/mini_utils_1.c \
		mandatory/map_check_1.c \
		mandatory/map_check_2.c \
		mandatory/init.c \
		mandatory/keypress.c \
		mandatory/so_long.c \

SRCB = bonus/mini_utils_1.c \
		bonus/mini_utils_2.c \
		bonus/map_check_1.c \
		bonus/map_check_2.c \
		bonus/init.c \
		bonus/keypress.c \
		bonus/movements.c \
		bonus/anim.c \
		bonus/player_anim.c \
		bonus/so_long_bonus.c \

NAME = so_long

BNAME = so_long_bonus

CFLAGS = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit

$(NAME) : $(SRCM) mandatory/so_long.h
	$(CC) $(CFLAGS) $(SRCM) -o $(NAME)

all : $(NAME)

$(BNAME) : $(SRCB) bonus/so_long_bonus.h
	$(CC) $(CFLAGS) $(SRCB) -o $(BNAME)

bonus : $(BNAME)

clean:
	rm -rf $(NAME)
	rm -rf $(BNAME)

fclean: clean

re : fclean all

