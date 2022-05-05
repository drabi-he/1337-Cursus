# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 11:07:28 by hdrabi            #+#    #+#              #
#    Updated: 2022/05/03 14:18:25 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ClapTrap.cpp \
		main.cpp 

HDR = ClapTrap.hpp 

NAME = OPEN

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all