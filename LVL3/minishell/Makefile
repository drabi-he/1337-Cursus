# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/10 10:48:44 by hdrabi            #+#    #+#              #
#    Updated: 2022/02/07 10:29:25 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCM = minishell.c

NAME = minishell

#CFLAGS = -Wall -Wextra -Werror -lreadline

all : $(NAME)

$(NAME) : $(SRCM)
	$(CC) $(CFLAGS) -lreadline $(SRCM) -o $(NAME)

clean :
	rm -f $(NAME)

fclean : clean

re : fclean all

