# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 13:36:05 by hdrabi            #+#    #+#              #
#    Updated: 2022/09/20 14:31:22 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.cpp \
		WebServ.cpp \
		Server.cpp \
		Location.cpp \
		utils.cpp \

HDR = main.hpp \
		WebServ.hpp \
		Server.hpp \
		Location.hpp \
		utils.hpp \

NAME = WebServ

CC = c++

# CFLAGS = -Wall -Werror -Wextra -std=c++98

all : $(NAME)

$(NAME) : $(SRC) $(HDR)
		$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean :
		rm -rf $(NAME)

fclean : clean

re : fclean all