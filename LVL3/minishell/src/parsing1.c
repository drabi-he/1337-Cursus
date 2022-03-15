/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:40:37 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/15 19:00:58 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define COUNT 20

void	ft_print_tree(t_tree *root, int space, int pos)
{
	if (root == NULL)
		return ;
	space += COUNT;
	ft_print_tree(root->right, space, pos + 1);
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("p %d | t %d| %s\n", pos, root->token, root->cmd? root->cmd[0] : "null");
	ft_print_tree(root->left, space, pos +1);
}

void	ft_tree_init(char *str)
{
	g_all.root = NULL;
	g_all.g_head = NULL;
	str = ft_strtrim(str, WHITESPACE);
	ft_fill_tree(&g_all.root, str, NULL);
	ft_print_tree(g_all.root, 0, 0);
}
