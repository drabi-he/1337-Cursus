/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:44:23 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/08 22:44:46 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mini_keypress(int keycode, t_key *key)
{
	if (keycode == 69 && key->move_speed < 0.5)
		key->move_speed += 0.01;
	if (keycode == 78 && key->move_speed > 0.02)
		key->move_speed -= 0.01;
	if (keycode == 126 && key->rot_speed < 0.5)
		key->rot_speed += 0.005;
	if (keycode == 125 && key->rot_speed > 0.006)
		key->rot_speed -= 0.005;
	print_instructions(key);
}

int	key_press(int keycode, t_all *all)
{
	t_key	*key;

	key = &all->key;
	if (keycode == 13)
		key->w = 1;
	if (keycode == 1)
		key->s = 1;
	if (keycode == 0)
		key->a = 1;
	if (keycode == 2)
		key->d = 1;
	if (keycode == 123)
		key->l = 1;
	if (keycode == 124)
		key->r = 1;
	if (keycode == 53)
		exit(1);
	mini_keypress(keycode, key);
	return (0);
}

int	key_release(int keycode, t_all *all)
{
	t_key	*key;

	key = &all->key;
	if (keycode == 13)
		key->w = 0;
	if (keycode == 1)
		key->s = 0;
	if (keycode == 0)
		key->a = 0;
	if (keycode == 2)
		key->d = 0;
	if (keycode == 123)
		key->l = 0;
	if (keycode == 124)
		key->r = 0;
	return (0);
}
