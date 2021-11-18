#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*copy;
	int		i;

	if (!str)
		return (NULL);
	copy = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (str[++i])
		copy[i] = str[i];
	copy[i] = '\0';
	return (copy);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	if (!str)
		return (NULL);
	if ((char)c == '\0')
		return ((char *)(str + ft_strlen(str)));
	i = -1;
	while (str[++i])
		if (str[i] == (char)c)
			return ((char *)(str + i));
	return (NULL);
}

t_line	*ft_lstnew(void *portion)
{
	t_line	*new;

	new = (t_line *)malloc(sizeof(t_line));
	if (!new)
		return (NULL);
	new->portion = portion;
	new->next = NULL;
	return (new);
}
