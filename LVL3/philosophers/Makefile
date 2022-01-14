# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/10 10:48:44 by hdrabi            #+#    #+#              #
#    Updated: 2022/01/14 18:03:47 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCM = philo/utils_1.c \
		philo/utils_2.c \
		philo/parsing.c \
		philo/philo.c \
		philo/exec.c

SRCB = philo_bonus/philo_bonus.c

NAME = philo_m

BNAME = philo_b

#CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(SRCM) philo/philo.h
	$(CC) $(CFLAGS) $(SRCM) -o $(NAME)

bonus : $(BNAME)

$(BNAME) : $(SRCB) philo_bonus/philo.h
	$(CC) $(CFLAGS) $(SRCB) -o $(BNAME)

clean :
	rm -f $(NAME)
	rm -f $(BNAME)

fclean : clean

re : fclean all

test : bonus
	./philo_bonus 3 200 200 200
