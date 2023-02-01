# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: izouf <izouf@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 13:36:05 by hdrabi            #+#    #+#              #
#    Updated: 2023/01/31 18:11:11 by izouf            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.cpp \
		WebServ.cpp \
		Server.cpp \
		Location.cpp \
		Client.cpp \
		Request.cpp \
		Response.cpp \
		Socket.cpp \
		utils.cpp \
		Cgi.cpp \

HDR = WebServ.hpp \
		Server.hpp \
		Location.hpp \
		Client.hpp \
		Request.hpp \
		Response.hpp \
		Socket.hpp \
		utils.hpp \
		Cgi.hpp \

NAME = WebServ

CC = c++

CFLAGS = -Wall -Werror -Wextra -std=c++98

all : $(NAME)

$(NAME) : $(SRC) $(HDR)
		$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean :
		rm -rf $(NAME)

fclean : clean

re : fclean all