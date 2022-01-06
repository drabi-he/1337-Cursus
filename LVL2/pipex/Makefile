# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 10:59:07 by hdrabi            #+#    #+#              #
#    Updated: 2022/01/06 18:00:55 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCM = srcs/utils_1.c \
		srcs/utils_2.c \
		srcs/utils_3.c \
		srcs/split.c \
		srcs/parsing.c \
		pipex.c

SRCB = srcs/utils_1.c \
		srcs/utils_2.c \
		srcs/utils_3.c \
		srcs/split.c \
		srcs/parsing.c \
		srcs/here_doc.c \
		pipex_bonus.c

NAME = pipex

BNAME = pipex_bonus

CFLAGS = -Wall -Wextra -Werror

$(NAME) : $(SRCM) pipex.h
	touch infile
	$(CC) $(CFLAGS) $(SRCM) -o $(NAME)

all : $(NAME)

$(BNAME) : $(SRCB) pipex.h
	touch infile
	$(CC) $(CFLAGS) $(SRCB) -o $(BNAME)

bonus : $(BNAME)

clean :
	rm -rf pipex pipex_bonus infile outfile .file_tmp

fclean : clean

re : fclean all
