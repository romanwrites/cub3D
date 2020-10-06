/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:41:05 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/25 17:45:20 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		move_w(t_game *sv)
{
	int mx_x;
	int mx_y;
	int my_x;
	int my_y;

	mx_x = (int)(sv->map.pos_x + sv->map.dir_x * MOVE_SPEED);
	mx_y = (int)(sv->map.pos_y);
	my_x = (int)(sv->map.pos_x);
	my_y = (int)(sv->map.pos_y + sv->map.dir_y * MOVE_SPEED);
	if (sv->map.map_arr[mx_x + mx_y * sv->map.max_len] != '1')
		sv->map.pos_x += sv->map.dir_x * MOVE_SPEED;
	if (sv->map.map_arr[my_x + my_y * sv->map.max_len] != '1')
		sv->map.pos_y += sv->map.dir_y * MOVE_SPEED;
}

void		move_s(t_game *sv)
{
	int mx_x;
	int mx_y;
	int my_x;
	int my_y;

	mx_x = (int)(sv->map.pos_x - sv->map.dir_x * MOVE_SPEED);
	mx_y = (int)(sv->map.pos_y);
	my_x = (int)(sv->map.pos_x);
	my_y = (int)(sv->map.pos_y - sv->map.dir_y * MOVE_SPEED);
	if (sv->map.map_arr[mx_x + mx_y * sv->map.max_len] != '1')
		sv->map.pos_x -= sv->map.dir_x * MOVE_SPEED;
	if (sv->map.map_arr[my_x + my_y * sv->map.max_len] != '1')
		sv->map.pos_y -= sv->map.dir_y * MOVE_SPEED;
}

void		move_a(t_game *sv)
{
	int mx_x;
	int mx_y;
	int my_x;
	int my_y;

	mx_x = (int)(sv->map.pos_x - sv->map.plane_x * MOVE_SPEED);
	mx_y = (int)(sv->map.pos_y);
	my_x = (int)(sv->map.pos_x);
	my_y = (int)(sv->map.pos_y - sv->map.plane_y * MOVE_SPEED);
	if (sv->map.map_arr[mx_x + mx_y * sv->map.max_len] != '1')
		sv->map.pos_x -= sv->map.plane_x * MOVE_SPEED;
	if (sv->map.map_arr[my_x + my_y * sv->map.max_len] != '1')
		sv->map.pos_y -= sv->map.plane_y * MOVE_SPEED;
}

void		move_d(t_game *sv)
{
	int mx_x;
	int mx_y;
	int my_x;
	int my_y;

	mx_x = (int)(sv->map.pos_x + sv->map.plane_x * MOVE_SPEED);
	mx_y = (int)(sv->map.pos_y);
	my_x = (int)(sv->map.pos_x);
	my_y = (int)(sv->map.pos_y + sv->map.plane_y * MOVE_SPEED);
	if (sv->map.map_arr[mx_x + mx_y * sv->map.max_len] != '1')
		sv->map.pos_x += sv->map.plane_x * MOVE_SPEED;
	if (sv->map.map_arr[my_x + my_y * sv->map.max_len] != '1')
		sv->map.pos_y += sv->map.plane_y * MOVE_SPEED;
}
