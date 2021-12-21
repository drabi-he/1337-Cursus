# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/11 14:59:58 by hdrabi            #+#    #+#              #
#    Updated: 2021/12/21 10:57:08 by hdrabi           ###   ########.fr        #
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

OBJM = ${SRCM:mandatory/.c=.o}

SRCB = bonus/

OBJB = ${SRCB:bonus/.c=.o}

NAME = push_swap

CFLAGS = -Wall -Wextra -Werror

$(NAME) : ${OBJM}
	$(CC) $(CFLAGS) ${OBJM} -o ${NAME}

all : $(NAME)

%.o : %.c mandatory/push_swap.h
	$(CC) $(CFLAGS) -c $<

clean :
	rm -rf ${OBJM} ${OBJB}

fclean : clean
	rm -rf ${NAME}

re : fclean all

bonus :
	$(CC) $(CFLAGS) ${OBJB} -o ${NAME}

################## testing #################

test :
	gcc push_swap.c -o push_swap
