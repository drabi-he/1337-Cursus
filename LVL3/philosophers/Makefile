# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/10 10:48:44 by hdrabi            #+#    #+#              #
#    Updated: 2022/01/13 11:23:15 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCM = philo.c

NAME = philo

#CFLAGS = -Wall -Wextra -Werror

$(NAME) : $(SRCM)
	$(CC) $(CFLAGS) $(SRCM) -o $(NAME)

all : $(NAME)

clean :
	rm -rf $(NAME)

fclean : clean

re : fclean all

test : all
	./philo 3 200 200 200
