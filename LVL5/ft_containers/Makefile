# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 10:58:52 by hdrabi            #+#    #+#              #
#    Updated: 2022/05/28 17:43:54 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.cpp

V_SRC = vectorTest.cpp

HDR = vector/vector.hpp

NAME = ft_containers

VNAME = V_TEST

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all : $(NAME)

$(NAME) : $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean :
	rm -rf $(NAME)
	rm -rf $(VNAME)

fclean : clean

re : fclean all 

$(VNAME) : $(V_SRC) $(HDR)
	$(CC) $(CFLAGS) $(V_SRC) -o $(VNAME)