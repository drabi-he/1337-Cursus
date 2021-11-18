#include "get_next_line.h"



void	free_ptr(void **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*get_next_line(int fd)
{
	static t_line	*list[4096];
	char			*rst;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 4096)
		return (NULL);
	if (!list[fd])
		list[fd] = ft_lstnew(ft_strdup(""));
	rst = get_line(&list[fd], list[fd], ft_strlen(list[fd]->portion), fd);
	return (rst);
}

char	*get_line(t_line **list, t_line *last, size_t len, int fd)
{
	char	*leftover;
	ssize_t	len_rd;
	t_line	*end;

	leftover = ft_strchr(last->portion, '\n');
	if (leftover)
	{
		len_rd = ft_strlen(leftover + 1);
		return (join_list( &list[0],len_rd, len));
	}
	leftover = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!leftover)
		return (NULL);
	len_rd = read(fd, leftover, BUFFER_SIZE);
	if (len_rd <= 0)
	{
		free_ptr((void **)&leftover);
		return (join_list(&list[0],len_rd, len ));
	}
	else
		len += len_rd;
	leftover[len_rd] = 0;
	end = ft_lstnew(leftover);
	last->next = end;
	return (get_line(&list[0], end, len, fd));
}

char	*join_list(t_line **list,size_t len_rd, size_t len)
{
	size_t		total_len;
	char	*result;

	//result = NULL;
	if (len <= 0)
	{
		free_ptr((void **)&list[0]->portion);
		free_ptr((void **)list);
		return (NULL);
	}
	total_len = len - len_rd;
	result = (char *)malloc((total_len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	result[total_len] = 0;
	convert_list(list, total_len, result);
	return (result);
}

void	convert_list(t_line **list, size_t total_len, char *result)
{
	t_line	*tmp;
	char	*leftover;
	size_t		i;
	size_t		j;

	i = 0;
	while (i < total_len)
	{
		j = 0;
		tmp = list[0];
		leftover = (char *)tmp->portion;
		while (leftover[j] && i < total_len)
			result[i++] = leftover[j++];
		if (leftover[j])
			list[0]->next = ft_lstnew(ft_strdup(leftover + j));
		list[0] = list[0]->next;
		free_ptr((void **)&tmp->portion);
		free_ptr((void **)&tmp);
	}
}
