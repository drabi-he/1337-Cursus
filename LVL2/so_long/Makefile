# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 11:27:12 by hdrabi            #+#    #+#              #
#    Updated: 2021/12/31 11:58:48 by hdrabi           ###   ########.fr        #
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
		bonus/so_long_bonus.c \

NAME = so_long

BNAME = so_long_bonus

CFLAGS = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit

$(NAME) : $(SRCM)
	$(CC) $(CFLAGS) $(SRCM) -o $(NAME)

all : $(NAME)

$(BNAME) : $(SRCB)
	$(CC) $(CFLAGS) $(SRCB) -o $(BNAME)

bonus : $(BNAME)

clean:
	rm -rf $(NAME)
	rm -rf $(BNAME)

fclean: clean

re : fclean all

