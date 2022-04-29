# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/27 14:24:34 by hdrabi            #+#    #+#              #
#    Updated: 2022/04/27 21:57:59 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = Contact.cpp \
		PhoneBook.cpp \
		main.cpp

HDR = Contact.hpp \
		PhoneBook.hpp \

NAME = phonebook

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all