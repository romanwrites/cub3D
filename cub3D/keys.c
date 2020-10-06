/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:47:27 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/25 18:17:05 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_buttons_state(t_game *sv)
{
	if (sv->keys.left)
		turn_left(sv);
	if (sv->keys.right)
		turn_right(sv);
	if (sv->keys.w)
		move_w(sv);
	if (sv->keys.s)
		move_s(sv);
	if (sv->keys.a)
		move_a(sv);
	if (sv->keys.d)
		move_d(sv);
}

int		press_key(int key, t_game *sv)
{
	if (key == W)
		sv->keys.w = 1;
	if (key == S)
		sv->keys.s = 1;
	if (key == A)
		sv->keys.a = 1;
	if (key == D)
		sv->keys.d = 1;
	if (key == LEFT)
		sv->keys.left = 1;
	if (key == RIGHT)
		sv->keys.right = 1;
	return (0);
}

int		release_key(int key, t_game *sv)
{
	if (key == W)
		sv->keys.w = 0;
	if (key == S)
		sv->keys.s = 0;
	if (key == A)
		sv->keys.a = 0;
	if (key == D)
		sv->keys.d = 0;
	if (key == LEFT)
		sv->keys.left = 0;
	if (key == RIGHT)
		sv->keys.right = 0;
	if (key == ESC)
		ft_close(key, sv);
	return (0);
}
