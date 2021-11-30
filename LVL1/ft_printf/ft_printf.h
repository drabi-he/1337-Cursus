/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:09:41 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/30 11:30:27 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "flags/ft_flags.h"
# include "libft/libft.h"
# include <stdio.h>
# define BASE "0123456789abcdef"

int	ft_printf(const char *str, ...);

#endif
