#!/bin/sh
find . -type d  -name ".v*" -exec rm -rf {} +
find . -type f \( -name '.Ds*' -o -name "a.out" \) -print
cd LVL0/libft && make fclean && cd ../..
cd LVL1/ft_printf && make fclean && cd ../..
cd LVL2/pipex && make fclean && cd ../..
cd LVL2/push_swap && make fclean && cd ../..
cd LVL2/so_long && make fclean && cd ../..
cd LVL3/minishell && make fclean && cd ../..
cd LVL3/philosophers/philo && make fclean && cd ../../..
cd LVL3/philosophers/philo_bonus && make fclean && cd ../../..
cd LVL4/cub3d && make fclean && cd ../..
cd LVL5/ft_containers && make fclean && cd ../..

