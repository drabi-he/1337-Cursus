/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:24:43 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/02 15:14:23 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_print_nbr(int nb, int *nb_len, t_print *lst)
{
	while (*nb_len < lst->precision || (nb < 0 && *nb_len - 1 < lst->precision))
	{
		ft_putchar_fd('0', 1);
		(*nb_len)++;
	}
	if (nb < 0)
		ft_putnbr_fd((unsigned)-nb, 1);
	else
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

static void	ft_dec_m_pr(t_print *lst, int nb, int *len)
{
	int	space_count;
	int	nb_len;

	space_count = lst->width - lst->precision;
	nb_len = ft_nbr_len(nb);
	if (ft_search_flag(lst->flags, '+') && nb >= 0)
	{
		ft_putchar_fd('+', 1);
		nb_len++;
	}
	if (ft_search_flag(lst->flags, ' ') && nb >= 0)
	{
		ft_putchar_fd(' ', 1);
		nb_len++;
	}
	if (nb < 0)
		ft_putchar_fd('-', 1);
	ft_print_nbr(nb, &nb_len, lst);
	(*len) += nb_len;
}

static void	ft_print_nbr2(int nb, int *nb_len, int precision, int width)
{
	int	i;

	i = ft_nbr_len(nb);
	while (i < precision || (nb < 0 && i - 1 < precision))
	{
		ft_putchar_fd('0', 1);
		i++;
		(*nb_len)++;
	}
	if (nb < 0)
		ft_putnbr_fd((unsigned)-nb, 1);
	else
		if (nb != 0 || precision != 0)
			ft_putnbr_fd(nb, 1);
	else
		if (width > 0)
			ft_putchar_fd(' ', 1);
	else
		(*nb_len)--;
}

static void	ft_dec_pr(t_print *lst, int nb, int *len)
{
	int	space_count;
	int	nb_len;
	int	i;

	i = -1;
	nb_len = ft_nbr_len(nb);
	space_count = ft_get_sp_count(lst->width, lst->precision, nb_len, nb);
	if ((ft_search_flag(lst->flags, '+')
			|| ft_search_flag(lst->flags, ' ')) && nb >= 0)
	{
		nb_len++;
		space_count--;
	}
	while (++i < space_count)
	{
		ft_putchar_fd(' ', 1);
		nb_len++;
	}
	ft_print_sign(lst->flags, nb);
	ft_print_nbr2(nb, &nb_len, lst->precision, lst->width);
	(*len) += nb_len;
}

void	ft_print_dec(t_print *lst, int nb, int *len)
{
	if (ft_search_flag(lst->flags, '-'))
		ft_dec_m_pr(lst, nb, len);
	else
	{
		if (lst->is_p)
			ft_dec_pr(lst, nb, len);
		else
			ft_dec_extra(lst->flags, lst->width, nb, len);
	}
}
