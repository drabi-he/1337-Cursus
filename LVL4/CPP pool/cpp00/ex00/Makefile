# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/27 14:24:34 by hdrabi            #+#    #+#              #
#    Updated: 2022/04/27 15:19:12 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = magaphone.cpp

NAME = megaphone

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all