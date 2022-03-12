# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/10 10:48:44 by hdrabi            #+#    #+#              #
#    Updated: 2022/03/12 17:39:51 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCM = minishell.c
SRCM1 = 1st_minishell.c

NAME = minishell

#CFLAGS = -Wall -Wextra -Werror -L$(shell brew --prefix readline)/lib -I$(shell brew --prefix readline)/include  -lreadline

CFLAGS = -L$(shell brew --prefix readline)/lib -I$(shell brew --prefix readline)/include  -lreadline

all : $(NAME)

$(NAME) : $(SRCM1)
	$(CC) $(CFLAGS)  $(SRCM1) -o $(NAME)
	clear
	./${NAME}

clean :
	rm -f $(NAME)

fclean : clean

re : fclean all

