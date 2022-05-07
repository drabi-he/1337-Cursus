# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 17:19:34 by hdrabi            #+#    #+#              #
#    Updated: 2022/05/05 15:51:13 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = AMateria.cpp \
		Character.cpp \
		MateriaSource.cpp \
		Cure.cpp \
		Ice.cpp \
		main.cpp 

HDR = AMateria.hpp \
		ICharacter.hpp \
		Character.hpp \
		Character.hpp \
		IMateriaSource.hpp \
		MateriaSource.hpp \
		Cure.hpp \
		Ice.hpp \

NAME = Interface

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all