# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 16:13:40 by hdrabi            #+#    #+#              #
#    Updated: 2021/11/27 13:58:40 by hdrabi           ###   ########.fr        #
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
	ft_putnbr_base.c

OBJS = $(SRCS:.c=.o)

NAME = libflags.a

CFLAGS = -Wall -Wextra -Werror -I.

$(NAME): $(OBJS) ft_flags.h
	ar cr $(NAME) $(OBJS)
	ranlib $(NAME)

all : $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
