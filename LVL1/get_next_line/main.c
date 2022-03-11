/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:31:04 by izouf             #+#    #+#             */
/*   Updated: 2022/03/11 13:50:51 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line ;

	fd = open("out", O_RDONLY | O_CREAT);

	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	// while (1)
	// {
	// 	line = get_next_line(fd);
	// 	printf("%s", line);
	// 	if (!line)
	// 		break ;
	// }
	// free(line);
	return (0);
}
