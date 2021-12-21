/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:52:39 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/21 15:07:02 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/push_swap.h"

void	ft_check_cmd(char *cmd)
{
	if (ft_strcmp(cmd, "sa\n") && ft_strcmp(cmd, "sb\n")
		&& ft_strcmp(cmd, "ss\n") && ft_strcmp(cmd, "pa\n")
		&& ft_strcmp(cmd, "pb\n") && ft_strcmp(cmd, "ra\n")
		&& ft_strcmp(cmd, "rb\n") && ft_strcmp(cmd, "rr\n")
		&& ft_strcmp(cmd, "rra\n") && ft_strcmp(cmd, "rrb\n")
		&& ft_strcmp(cmd, "rrr\n"))
	{
		write(1, "Error\n", 6);
		exit(0);
	}
}

void	ft_buff_to_zero(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = 0;
		i++;
	}
}

void	ft_choose_action(t_stack **a, t_stack **b, char *cmd)
{
	if (!ft_strcmp(cmd, "sa\n"))
		ft_swap_a(a, 0);
	else if (!ft_strcmp(cmd, "sb\n"))
		ft_swap_b(b, 0);
	else if (!ft_strcmp(cmd, "ss\n"))
		ft_ss(a, b, 0);
	else if (!ft_strcmp(cmd, "pa\n"))
		ft_push_a(b, a, 0);
	else if (!ft_strcmp(cmd, "pb\n"))
		ft_push_b(a, b, 0);
	else if (!ft_strcmp(cmd, "ra\n"))
		ft_rotate_a(a, 0);
	else if (!ft_strcmp(cmd, "rb\n"))
		ft_rotate_b(b, 0);
	else if (!ft_strcmp(cmd, "rr\n"))
		ft_rr(a, b, 0);
	else if (!ft_strcmp(cmd, "rra\n"))
		ft_reverse_rotate_a(a, 0);
	else if (!ft_strcmp(cmd, "rrb\n"))
		ft_reverse_rotate_a(b, 0);
	else if (!ft_strcmp(cmd, "rrr\n"))
		ft_rrr(a, b, 0);
}

int	main(int ac, char *av[])
{
	t_stack	*a;
	t_stack	*b;
	char	**str;
	char	buff[5];

	str = ft_split(ft_strjoin(ac, av, " "), ' ');
	a = ft_devide_args(str);
	while (read(0, buff, 4))
	{
		ft_check_cmd(buff);
		ft_choose_action(&a, &b, buff);
		ft_buff_to_zero(buff);
	}
	if (ft_check_sort(a) && ft_lstcount(b) == 0)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	return (ac);
}
