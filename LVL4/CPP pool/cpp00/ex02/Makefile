# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/27 14:24:34 by hdrabi            #+#    #+#              #
#    Updated: 2022/04/28 01:24:01 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = Account.cpp \
		tests.cpp

HDR = Account.hpp

NAME = Accounts

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all