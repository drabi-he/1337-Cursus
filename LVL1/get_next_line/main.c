/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:31:04 by izouf             #+#    #+#             */
/*   Updated: 2021/11/25 14:25:20 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd = open("l", O_RDONLY | O_CREAT);
	/* int fd1 = open("test1", O_RDONLY | O_CREAT);
	  int fd2 = open("test2", O_RDONLY | O_CREAT);
	   int fd3 = open("test3", O_RDONLY | O_CREAT);
	    int fd4 = open("test4", O_RDONLY | O_CREAT);
		 int fd5 = open("test5", O_RDONLY | O_CREAT);
		  int fd6 = open("test6", O_RDONLY | O_CREAT);*/
		char *line ;
		while ((line = get_next_line(fd)))
			printf("%s", line);
		/*line = get_next_line(fd);
        printf("%s", line);
		line = get_next_line(fd);
        printf("%s", line);*/
		/*line = get_next_line(fd2);
		printf("%p\n",line);
        printf("%s", line);
		line = get_next_line(fd3);
		printf("%p\n",line);
        printf("%s", line);
		line = get_next_line(fd4);
        printf("%s", line);
		line = get_next_line(fd5);
        printf("%s", line);
		line = get_next_line(fd6);
        printf("%s", line);
		line = get_next_line(fd);
        printf("%s", line);
		line = get_next_line(fd1);
        printf("%s", line);
		line = get_next_line(fd2);
        printf("%s", line);
		line = get_next_line(fd3);
        printf("%s", line);
		line = get_next_line(fd4);
        printf("%s", line);
		line = get_next_line(fd5);
        printf("%s", line);
		line = get_next_line(fd6);
        printf("%s", line);
		     close(fd);
			      close(fd1);
				       close(fd2);
					        close(fd3);
							     close(fd4);
								      close(fd5);
									       close(fd6);*/
	free(line);
	return (0);
}
