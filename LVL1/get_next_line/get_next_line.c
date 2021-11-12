/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:53:44 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/12 12:47:19 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int		r;
	char	*rst;

	rst = (char *)malloc((BUFF_SIZE +1) * sizeof(char));
	if (!rst)
		return (NULL);
	r = read(fd, rst, BUFF_SIZE);
	rst[BUFF_SIZE] = 0 ;
	//printf("fd = %d | read = %d | string = %s\n",fd,r,rst);
	return (rst);
}
