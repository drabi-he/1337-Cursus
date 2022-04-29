# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 13:43:03 by hdrabi            #+#    #+#              #
#    Updated: 2022/04/29 13:43:23 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = Fixed.cpp \
		main.cpp 

HDR = Fixed.hpp 

NAME = Fixed

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all