# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/01 16:13:55 by hdrabi            #+#    #+#              #
#    Updated: 2021/12/01 18:46:22 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror -c

NAME = libftprintf.a

${NAME}: EXTRA1 ${OBJS}
	ar rc $@ ${OBJS} flags/*.o

all : ${NAME}

%.o : %.c ft_printf.h
	$(CC) $(CFLAGS) $^

clean :
	cd flags && make clean
	rm -rf ${OBJS} *.gch

fclean : clean
	cd flags && make fclean
	rm -rf ${NAME}

EXTRA1:
	cd flags && make

bonus : all

re : fclean all

test: all
	gcc main.c $(NAME)
	clear && ./a.out

