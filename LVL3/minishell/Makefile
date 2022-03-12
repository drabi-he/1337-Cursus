# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/10 10:48:44 by hdrabi            #+#    #+#              #
#    Updated: 2022/03/12 12:48:33 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCM = minishell.c

NAME = minishell

#CFLAGS = -Wall -Wextra -Werror -lreadline

all : $(NAME)

$(NAME) : $(SRCM)
	$(CC) $(CFLAGS) -L$(shell brew --prefix readline)/lib -I$(shell brew --prefix readline)/include -lreadline $(SRCM) -o $(NAME)
	./${NAME}

clean :
	rm -f $(NAME)

fclean : clean

re : fclean all

