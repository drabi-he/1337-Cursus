# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/11 14:59:58 by hdrabi            #+#    #+#              #
#    Updated: 2022/02/28 10:43:26 by hdrabi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCM = mandatory/ft_strjoin.c \
		mandatory/ft_split.c \
		mandatory/ft_actions_1.c \
		mandatory/ft_actions_2.c \
		mandatory/ft_actions_3.c \
		mandatory/ft_last_step.c \
		mandatory/ft_others.c \
		mandatory/ft_prepare_a.c \
		mandatory/ft_tab_utils.c \
		mandatory/ft_utils_1.c \
		mandatory/ft_utils_2.c \
		mandatory/ft_utils_3.c \
		mandatory/ft_verfiy.c \
		mandatory/push_swap.c \

SRCB = mandatory/ft_strjoin.c \
		mandatory/ft_split.c \
		mandatory/ft_actions_1.c \
		mandatory/ft_actions_2.c \
		mandatory/ft_actions_3.c \
		mandatory/ft_last_step.c \
		mandatory/ft_others.c \
		mandatory/ft_prepare_a.c \
		mandatory/ft_tab_utils.c \
		mandatory/ft_utils_1.c \
		mandatory/ft_utils_2.c \
		mandatory/ft_utils_3.c \
		mandatory/ft_verfiy.c \
		bonus/checker.c

NAME = push_swap
BNAME = checker

CFLAGS = -Wall -Wextra -Werror

$(NAME) : ${SRCM} mandatory/push_swap.h
	$(CC) $(CFLAGS) ${SRCM} -o ${NAME}

all : $(NAME)

$(BNAME) :${SRCB} mandatory/push_swap.h
	$(CC) $(CFLAGS) ${SRCB} -o checker

bonus : $(BNAME)

clean :

fclean : clean
	rm -rf ${NAME} $(BNAME)

re : fclean all

