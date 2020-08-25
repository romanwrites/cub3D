/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turns.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:43:27 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/25 17:46:19 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		turn_left(t_game *sv)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = sv->map.dir_x;
	old_plane_x = sv->map.plane_x;
	sv->map.dir_x = sv->map.dir_x * cos(-ROT) - sv->map.dir_y * sin(-ROT);
	sv->map.dir_y = old_dir_x * sin(-ROT) + sv->map.dir_y * cos(-ROT);
	sv->map.plane_x = sv->map.plane_x * cos(-ROT) - sv->map.plane_y * sin(-ROT);
	sv->map.plane_y = old_plane_x * sin(-ROT) + sv->map.plane_y * cos(-ROT);
}

void		turn_right(t_game *sv)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = sv->map.dir_x;
	old_plane_x = sv->map.plane_x;
	sv->map.dir_x = sv->map.dir_x * cos(ROT) - sv->map.dir_y * sin(ROT);
	sv->map.dir_y = old_dir_x * sin(ROT) + sv->map.dir_y * cos(ROT);
	sv->map.plane_x = sv->map.plane_x * cos(ROT) - sv->map.plane_y * sin(ROT);
	sv->map.plane_y = old_plane_x * sin(ROT) + sv->map.plane_y * cos(ROT);
}
