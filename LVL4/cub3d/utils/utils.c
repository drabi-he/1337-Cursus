/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 23:04:16 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/09 22:13:00 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_error(char *str, int exit_status)
{
	write(2, str, ft_strlen(str));
	exit(exit_status);
	return (exit_status);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	if ((char)c == '\0')
		return ((char *)(s + ft_strlen(s)));
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

void	load_img(void *mlx, t_texture	*t, char *filename)
{
	int	w;
	int	h;

	t->img = mlx_xpm_file_to_image(mlx, filename, &w, &h);
	if (t->img == NULL)
		ft_error("Error: xpm file corrupt\n", 1);
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->sl, &t->en);
}

float	f_abs(float n)
{
	if (n >= 0)
		return (n);
	return (-n);
}

void	print_instructions(t_key *key)
{
	printf("\n\n\n\n\n");
	printf("\t\t\t\t/**********************************************/\n");
	printf("\t\t\t\t/*                INSTRUCTIONS                */\n");
	printf("\t\t\t\t/**********************************************/\n");
	printf("\t\t\t\t/*             W : move forward               */\n");
	printf("\t\t\t\t/*             A : move left                  */\n");
	printf("\t\t\t\t/*             S : move backward              */\n");
	printf("\t\t\t\t/*             D : move right                 */\n");
	printf("\t\t\t\t/*             \u2190 : rotate camera left         */\n");
	printf("\t\t\t\t/*             \u2192 : rotate camera right        */\n");
	printf("\t\t\t\t/*             + : increase move speed        */\n");
	printf("\t\t\t\t/*             - : decrease move speed        */\n");
	printf("\t\t\t\t/*             \u2191 : increase rot speed         */\n");
	printf("\t\t\t\t/*             \u2193 : decrease rot speed         */\n");
	printf("\t\t\t\t/**********************************************/\n");
	printf("\t\t\t\t/*   move speed : %3d %% | rot speed : %3d %%   */\n", \
	(int)(key->move_speed * 100 / 0.5) - 1, (int)(key->rot_speed * 100 / 0.5));
	printf("\t\t\t\t/**********************************************/\n");
	printf("\n\n\n\n\n");
}
