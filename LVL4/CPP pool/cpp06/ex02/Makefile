# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 15:05:28 by hdrabi            #+#    #+#              #
#    Updated: 2022/05/09 19:20:57 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = Base.cpp \
		A.cpp \
		B.cpp \
		C.cpp \
		main.cpp 

HDR = Base.hpp \
		A.hpp \
		B.hpp \
		C.hpp \

NAME = DynamicCasting

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all