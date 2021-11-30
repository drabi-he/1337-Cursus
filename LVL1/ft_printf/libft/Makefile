# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 14:24:02 by hdrabi            #+#    #+#              #
#    Updated: 2021/11/30 11:28:36 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCM = ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_split.c \
ft_strchr.c \
ft_strdup.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c
OBJM = $(SRCM:.c=.o)
SRCB = ft_lstnew.c \
ft_lstadd_front.c \
ft_lstsize.c \
ft_lstlast.c \
ft_lstadd_back.c \
ft_lstdelone.c \
ft_lstclear.c \
ft_lstiter.c \
ft_lstmap.c
OBJB = $(SRCB:.c=.o)
CFLAGS = -Wall -Wextra -Werror -I. -c
NAME = libft.a


$(NAME):$(OBJM)
	ar cr $(NAME) $^
	ranlib $(NAME)

all:$(NAME)

bonus :$(OBJM) $(OBJB)
	ar cr $(NAME) $^
	ranlib $(NAME)

%.o : %.c libft.h
	$(CC) $(CFLAGS) $^

clean:
	rm -rf $(OBJM) $(OBJB)

fclean: clean
	rm -rf $(NAME)

re: fclean all
