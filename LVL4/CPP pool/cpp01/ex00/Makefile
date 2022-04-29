# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/28 15:02:05 by hdrabi            #+#    #+#              #
#    Updated: 2022/04/28 15:05:52 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = newZombie.cpp \
		randomChump.cpp \
		Zombie.cpp \
		main.cpp 

HDR = Zombie.hpp

NAME = BraiiiiiiinnnzzzZ

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all