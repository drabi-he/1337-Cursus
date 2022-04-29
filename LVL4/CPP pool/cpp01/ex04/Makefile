# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/28 22:28:31 by hdrabi            #+#    #+#              #
#    Updated: 2022/04/29 00:00:00 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = Replace.cpp \
		main.cpp 

HDR = Replace.hpp 

NAME = Replace

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all