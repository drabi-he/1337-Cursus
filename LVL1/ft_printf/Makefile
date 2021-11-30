# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 13:16:41 by hdrabi            #+#    #+#              #
#    Updated: 2021/11/30 17:04:03 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c

OBJS = $(SRCS:.c=.o)

MAKE = make

CFLAGS = -Wall -Wextra -Werror -I. -c

NAME = libftprintf.a

$(NAME): EXTRA1 EXTRA2 $(OBJS)
	ar cr $(NAME) $(OBJS) libft/*.o flags/*.o
	ranlib $(NAME)

all : $(NAME)

%.o : %.c ft_printf.h
	$(CC) $(CFLAGS) $^

clean :
	rm -rf $(OBJS)
	cd libft && make clean
	cd flags && make clean

fclean : clean
	rm -rf $(NAME)
	cd libft && make fclean
	cd flags && make fclean

re :fclean all

bonus : all

EXTRA1 :
	cd libft && $(MAKE) bonus

EXTRA2 :
	cd flags && $(MAKE)

############# test ###############
test: all
	cd .. && gcc  main.c ft_printf/libftprintf.a
	cd .. && clear && ./a.out
