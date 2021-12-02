# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/01 16:09:19 by hdrabi            #+#    #+#              #
#    Updated: 2021/12/02 17:48:14 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_divide_str.c \
		ft_utils_1.c \
		ft_utils_2.c \
		ft_libft_utils_1.c \
		ft_libft_utils_2.c \
		ft_check_all.c \
		ft_print_char.c \
		ft_print_str.c \
		ft_print_addr.c \
		ft_print_dec.c \
		ft_print_dec_2.c \
		ft_print_un.c \
		ft_print_un_2.c \
		ft_print_hex.c \
		ft_print_hex_2.c \
		ft_print_percent.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror -c

NAME = libflags.a

${NAME}: ${OBJS}
	ar rc $@ $<

all : ${NAME}

%.o : %.c ft_flags.h
	$(CC) $(CFLAGS) $^

clean :
	rm -rf ${OBJS} *.gch

fclean : clean
	rm -rf ${NAME}

re : fclean all
