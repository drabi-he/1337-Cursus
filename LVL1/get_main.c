#include "get_next_line/get_next_line.h"
#include <stdio.h>

int main()
{
	int fd = open("get_next_line/get_next_line.c", O_RDONLY , S_IRUSR);
	printf("fd = %d | string = %s\n",fd,get_next_line(fd));
}
