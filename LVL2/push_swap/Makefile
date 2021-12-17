# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/11 14:59:58 by hdrabi            #+#    #+#              #
#    Updated: 2021/12/17 10:36:12 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = push_swap.c

OBJS = ${SRCS:.c=.o}

NAME = libpushswap.a

CFLAGS = -Wall -Wextra -Werror

$(NAME) : ${OBJS}


all : $(NAME)

%.o : %.c push_swap.h
	$(CC) $(CFLAGS) -c $<

clean :
	rm -rf ${OBJS}

fclean : clean
	rm -rf ${NAME}

re : fclean all

compile : re
	$(CC) $(CFLAGS) push_swap.c ${NAME} -o push_swap


################## testing #################

test :
	gcc push_swap.c -o push_swap
