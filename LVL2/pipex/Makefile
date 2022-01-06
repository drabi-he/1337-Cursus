# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 10:59:07 by hdrabi            #+#    #+#              #
#    Updated: 2022/01/06 13:53:42 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCM = mandtory/

SRCB = bonus/

NAME = pipex

#BNAME = pipex

#CFLAGS = -Wall -Wextra -Werror

$(NAME) : $(SRCM) pipex.h
	$(CC) $(CFLAGS) $(SRCM) -o $(NAME)

all : $(NAME)

$(BNAME) : $(SRCB) pipex.h
	$(CC) $(CFLAGS) $(SRCB) -o $(BNAME)

bonus : $(BNAME)

clean :
	rm -rf pipex

fclean : clean

re : fclean all


test :
	$(CC) $(CFLAGS) pipex_bonus.c -o pipex
