# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 15:05:28 by hdrabi            #+#    #+#              #
#    Updated: 2022/05/09 19:20:48 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = utils.cpp \
		main.cpp 

HDR = header.hpp \

NAME = ReinterpretCasting

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all