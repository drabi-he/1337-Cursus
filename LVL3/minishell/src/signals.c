/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:11:04 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/17 11:34:23 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handel_ctl(int sig)
{
	if (g_all.status_s && sig == SIGINT)
	{
		kill(g_all.pid, SIGINT);
		write(1, "\n", 1);
		return ;
	}
	if (!g_all.status_s)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

void	handel_ctl1(int sig)
{
	if (g_all.status_s && sig == SIGQUIT)
	{
		kill(g_all.pid, SIGQUIT);
		write(1, "Quit: 3\n", 8);
		return ;
	}
	if (!g_all.status_s && sig == SIGQUIT)
	{
		write(1, "\r", 1);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}
