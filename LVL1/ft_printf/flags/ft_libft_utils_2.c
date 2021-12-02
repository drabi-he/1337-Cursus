/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:45:38 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/02 13:19:31 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

void	ft_putnbr_fd(long long n, int fd)
{
	unsigned int	nb;

	if (fd < 0)
		return ;
	if (n < 0)
	{
		nb = -n;
		ft_putchar_fd('-', fd);
	}
	else
		nb = n;
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	ft_putchar_fd(nb % 10 + 48, fd);
}

void	ft_print(size_t n, size_t size, int form, int *l)
{
	if (n > size - 1)
	{
		ft_print(n / size, size, form, l);
		n %= size;
	}
	(*l)++;
	if (n > 9)
		ft_putchar_fd(BASE[n] - form, 1);
	else
		ft_putchar_fd(BASE[n], 1);
}

void	ft_putnbr_base(size_t nbr, int form, int *l)
{
	size_t	n;
	size_t	size;

	if (nbr < 0)
	{
		n = -nbr;
		ft_putchar_fd('-', 1);
	}
	else
	n = nbr;
	size = ft_strlen(BASE);
	ft_print(n, size, form, l);
}
