# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 10:58:52 by hdrabi            #+#    #+#              #
#    Updated: 2022/11/12 12:36:55 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.cpp

X_SRC = xtraTest.cpp

V_SRC = vectorTest.cpp

S_SRC = stackTest.cpp

M_SRC = mapTest.cpp

ST_SRC = setTest.cpp

HDR = xtra/enable_if.hpp \
		xtra/is_integral.hpp \
		xtra/equal.hpp \
		xtra/lexicographical_compare.hpp \
		iterators/iterator.hpp\
		iterators/iterator_traits.hpp\
		vector/vector.hpp \
		stack/stack.hpp \
		redBlackTree/RedBlackTree.hpp \
		map/map.hpp \
		set/set.hpp \

NAME = ft_containers

XNAME = XTRA_exec

VNAME = Vector_exec

SNAME = Stack_exec

MNAME = Map_exec

STNAME = Set_exec

CC = c++

# CFLAGS = -Wall -Wextra -Werror -std=c++98

all : $(NAME)

$(NAME) : $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean :
	rm -rf $(NAME)
	rm -rf $(XNAME)
	rm -rf $(VNAME)
	rm -rf $(SNAME)
	rm -rf $(MNAME)
	rm -rf $(STNAME)

fclean : clean

re : fclean all all2

all2 : $(XNAME) $(VNAME) $(SNAME) $(MNAME) $(STNAME)

$(XNAME) : $(X_SRC) $(HDR)
	$(CC) $(CFLAGS) $(X_SRC) -o $(XNAME)

$(VNAME) : $(V_SRC) $(HDR)
	$(CC) $(CFLAGS) $(V_SRC) -o $(VNAME)

$(SNAME) : $(S_SRC) $(HDR)
	$(CC) $(CFLAGS) $(S_SRC) -o $(SNAME)

$(MNAME) : $(M_SRC) $(HDR)
	$(CC) $(CFLAGS) $(M_SRC) -o $(MNAME)

$(STNAME) : $(ST_SRC) $(HDR)
	$(CC) $(CFLAGS) $(ST_SRC) -o $(STNAME)