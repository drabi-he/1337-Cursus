# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 11:27:12 by hdrabi            #+#    #+#              #
#    Updated: 2021/12/27 19:01:31 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCM = mandatory/

SRCB = bonus/

NAME = so_long

#CFLAGS = -Wall -Wextra -Werror

$(NAME) : $(SRCM)
	$(CC) $(CFLAGS) $(SRCM) -o $(NAME)

all : $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re : fclean all

test:
	gcc so_long.c -o so_long -lmlx -framework OpenGL -framework AppKit
