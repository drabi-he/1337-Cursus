# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/10 10:48:44 by hdrabi            #+#    #+#              #
#    Updated: 2022/03/05 14:59:34 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCB = utils1.c \
		utils2.c \
		parsing.c \
		exec.c \
		philo_bonus.c

NAME = philo_bonus

CFLAGS = -Wall -Wextra -Werror

bonus : $(NAME)

$(NAME) : $(SRCB) philo_bonus.h
	$(CC) $(CFLAGS) $(SRCB) -o $(NAME)

clean :
	rm -f $(NAME)

fclean : clean

re : fclean all
