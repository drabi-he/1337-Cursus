# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 10:58:52 by hdrabi            #+#    #+#              #
#    Updated: 2022/05/31 19:59:15 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.cpp

X_SRC = xtraTest.cpp

V_SRC = vectorTest.cpp

HDR = xtra/enable_if.hpp \
		xtra/is_integral.hpp \
		xtra/equal.hpp \
		xtra/lexicographical_compare.hpp \
		vector/vector.hpp

NAME = ft_containers

XNAME = XTRA_exec

VNAME = Vector_exec

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all : $(NAME)

$(NAME) : $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean :
	rm -rf $(NAME)
	rm -rf $(XNAME)
	rm -rf $(VNAME)

fclean : clean

re : fclean all 

all2 : $(XNAME) $(VNAME)

$(XNAME) : $(X_SRC) $(HDR)
	$(CC) $(CFLAGS) $(X_SRC) -o $(XNAME)

$(VNAME) : $(V_SRC) $(HDR)
	$(CC) $(CFLAGS) $(V_SRC) -o $(VNAME)