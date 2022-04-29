# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/28 17:02:44 by hdrabi            #+#    #+#              #
#    Updated: 2022/04/28 17:06:22 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = Weapon.cpp \
		HumanA.cpp \
		HumanB.cpp \
		main.cpp 

HDR = Weapon.hpp \
		HumanA.hpp \
		HumanB.hpp

NAME = Violence

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all