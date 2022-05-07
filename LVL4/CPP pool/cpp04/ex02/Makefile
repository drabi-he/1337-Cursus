# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 10:51:22 by hdrabi            #+#    #+#              #
#    Updated: 2022/05/04 16:27:39 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = Animal.cpp \
		Cat.cpp \
		Dog.cpp \
		Brain.cpp \
		main.cpp 

HDR = Animal.hpp \
		Cat.hpp \
		Dog.hpp \
		Brain.hpp 

NAME = Animal

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all