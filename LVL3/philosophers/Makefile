# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/10 10:48:44 by hdrabi            #+#    #+#              #
#    Updated: 2022/02/21 11:29:19 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCM = philo/utils_1.c \
		philo/utils_2.c \
		philo/parsing.c \
		philo/philo.c \
		philo/exec.c

SRCB = philo_bonus/utils1.c \
		philo_bonus/utils2.c \
		philo_bonus/parsing.c \
		philo_bonus/exec.c \
		philo_bonus/philo_bonus.c

NAME = philo_m

BNAME = philo_b

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(SRCM) philo/philo.h
	$(CC) $(CFLAGS) $(SRCM) -o $(NAME)

bonus : $(BNAME)

$(BNAME) : $(SRCB) philo_bonus/philo_bonus.h
	$(CC) $(CFLAGS) $(SRCB) -o $(BNAME)

clean :
	rm -f $(NAME)
	rm -f $(BNAME)

fclean : clean

re : fclean all
