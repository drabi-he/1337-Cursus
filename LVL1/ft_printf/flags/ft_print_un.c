/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_un.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:31:46 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/02 16:33:28 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_print_nbr(unsigned int nb, int *nb_len, t_print *lst)
{
	while (*nb_len < lst->precision)
	{
		ft_putchar_fd('0', 1);
		(*nb_len)++;
	}
	if (nb != 0 || lst->precision != 0)
		ft_putnbr_fd(nb, 1);
	if (nb == 0 && !lst->is_p)
		ft_putnbr_fd(nb, 1);
	if (nb == 0 && lst->precision == 0 && lst->is_p)
		ft_putchar_fd(' ', 1);
	while (*nb_len < lst->width)
	{
		ft_putchar_fd(' ', 1);
		(*nb_len)++;
	}
}

static void	ft_un_m_pr(t_print *lst, unsigned int nb, int *len)
{
	int	space_count;
	int	nb_len;

	space_count = lst->width - lst->precision;
	nb_len = ft_nbr_len(nb);
	if (nb < 0)
		ft_putchar_fd('-', 1);
	ft_print_nbr(nb, &nb_len, lst);
	(*len) += nb_len;
}

static void	ft_print_nbr2(long long nb, int *nb_len, int precision)
{
	int	i;

	i = ft_nbr_len(nb);
	while (i < precision || (nb < 0 && i - 1 < precision))
	{
		ft_putchar_fd('0', 1);
		i++;
		(*nb_len)++;
	}
	ft_putnbr_fd(nb, 1);
}

static void	ft_un_pr(int width, int precision, unsigned int nb, int *len)
{
	int	space_count;
	int	nb_len;
	int	i;

	i = -1;
	nb_len = ft_nbr_len(nb);
	space_count = ft_get_sp_count(width, precision, nb_len, nb);
	if (nb == 0 && precision == 0)
		nb_len--;
	while (++i < space_count)
	{
		ft_putchar_fd(' ', 1);
		nb_len++;
	}
	if (nb != 0 || precision != 0)
		ft_print_nbr2(nb, &nb_len, precision);
	else
	{
		if (width > 0)
		{
			ft_putchar_fd(' ', 1);
			nb_len++;
		}
	}
	(*len) += nb_len;
}

void	ft_print_un(t_print *lst, unsigned int nb, int *len)
{
	if (ft_search_flag(lst->flags, '-'))
		ft_un_m_pr(lst, nb, len);
	else
	{
		if (lst->is_p)
			ft_un_pr(lst->width, lst->precision, nb, len);
		else
			ft_un_extra(lst->flags, lst->width, nb, len);
	}
}
