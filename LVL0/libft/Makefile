# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 14:24:02 by hdrabi            #+#    #+#              #
#    Updated: 2021/11/06 19:22:11 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_atoi.c	ft_bzero.c	ft_calloc.c	ft_isalnum.c	ft_isalpha.c	ft_isascii.c	ft_isdigit.c	ft_isprint.c	ft_itoa.c	ft_memchr.c	ft_memcmp.c	ft_memcpy.c	ft_memmove.c	ft_memset.c	ft_putchar_fd.c	ft_putendl_fd.c	ft_putnbr_fd.c	ft_putstr_fd.c	ft_split.c	ft_strchr.c	ft_strdup.c	ft_striteri.c	ft_strjoin.c	ft_strlcat.c	ft_strlcpy.c	ft_strlen.c	ft_strmapi.c	ft_strncmp.c	ft_strnstr.c	ft_strrchr.c	ft_strtrim.c	ft_substr.c	ft_tolower.c	ft_toupper.c
NAME = libft.a
OBJS = $(SRCS:.c=.o) $(SRCB:.c=.o)
FLAGS = gcc -Wall -Wextra -Werror
SRCB = ft_lstnew.c	ft_lstadd_front.c	ft_lstsize.c	ft_lstlast.c	ft_lstadd_back.c	ft_lstdelone.c	ft_lstclear.c	ft_lstiter.c	ft_lstmap.c

$(NAME):$(OBJS)
	$(FLAGS) -c $(SRCS) -I libft.h
	ar cr $@ $^

all:$(NAME)

bonus :
	$(FLAGS) -c $(SRCB) $(SRCS) -I libft.h
	ar cr $(NAME) $(OBJS)

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all
