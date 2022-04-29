# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 00:04:52 by hdrabi            #+#    #+#              #
#    Updated: 2022/04/29 00:06:03 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = Harl.cpp \
		main.cpp 

HDR = Harl.hpp 

NAME = Harl2.0

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all