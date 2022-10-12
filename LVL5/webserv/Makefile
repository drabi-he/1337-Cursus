# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 13:36:05 by hdrabi            #+#    #+#              #
#    Updated: 2022/10/06 12:22:57 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.cpp \
		WebServ.cpp \
		Server.cpp \
		Location.cpp \
		Socket.cpp \
		Client.cpp \
		Request.cpp \
		utils.cpp \
		utils2.cpp \

HDR = main.hpp \
		WebServ.hpp \
		Server.hpp \
		Location.hpp \
		Socket.hpp \
		Client.hpp \
		Request.hpp \
		utils.hpp \
		utils2.hpp \

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