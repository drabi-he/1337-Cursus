# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/10 10:48:44 by hdrabi            #+#    #+#              #
#    Updated: 2022/03/05 14:59:55 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCM = utils_1.c \
		utils_2.c \
		parsing.c \
		philo.c \
		exec.c


NAME = philo

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(SRCM) philo.h
	$(CC) $(CFLAGS) $(SRCM) -o $(NAME)

clean :
	rm -f $(NAME)

fclean : clean

re : fclean all
