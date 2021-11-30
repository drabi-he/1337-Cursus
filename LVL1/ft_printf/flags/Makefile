# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 16:13:40 by hdrabi            #+#    #+#              #
#    Updated: 2021/11/30 18:15:08 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_devide.c \
	ft_create_lst.c \
	ft_utils.c \
	ft_check_valid.c \
	ft_get_results.c \
	ft_print_char.c \
	ft_print_all.c \
	ft_print_str.c \
	ft_print_ptr.c \
	ft_putnbr_base.c \
	ft_print_dec.c \
	ft_dec_multi_flags.c \
	ft_print_un.c \
	ft_un_0.c \
	ft_print_hex.c

OBJS = $(SRCS:.c=.o)

NAME = libflags.a

CFLAGS = -Wall -Wextra -Werror -I. -c

$(NAME): $(OBJS)
	ar cr $(NAME) $(OBJS)
	ranlib $(NAME)

all : $(NAME)

%.o : %.c ft_flags.h
	$(CC) $(CFLAGS) $^

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
