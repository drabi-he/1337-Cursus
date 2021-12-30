# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 11:27:12 by hdrabi            #+#    #+#              #
#    Updated: 2021/12/30 16:55:01 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCM = mandatory/

SRCB = bonus/

NAME = so_long

CFLAGS = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit

$(NAME) : $(SRCM)
	$(CC) $(CFLAGS) $(SRCM) -o $(NAME)

all : $(NAME)

bonus :
	$(CC) $(CFLAGS) $(SRCB) -o $(NAME)
clean:

fclean: clean
	rm -rf $(NAME)

re : fclean all

test:
	gcc $(CFLAGS) so_long.c -o so_long
