# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 14:24:02 by hdrabi            #+#    #+#              #
#    Updated: 2021/11/01 18:24:22 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = $(wildcard *.c)
NAME = libft.a
OBJS = $(SRCS:.c=.o)
FLAGS = gcc -Wall -Wextra -Werror

$(NAME):$(OBJS)
	$(FLAGS) -c $(SRCS) -I libft.h
	ar cr $@ $^

all:$(NAME)

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all
