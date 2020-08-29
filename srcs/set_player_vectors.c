/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_vectors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:50:41 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/26 18:50:49 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		set_dir_and_plane_no_so(t_game *sv, int j, int i)
{
	if (sv->map.map_array[j] == 'N')
	{
		sv->map.dir_x = 0;
		sv->map.dir_y = -0.66;
		sv->map.plane_x = 0.66;
		sv->map.plane_y = 0;
	}
	else if (sv->map.map_array[j] == 'S')
	{
		sv->map.dir_x = 0;
		sv->map.dir_y = 1;
		sv->map.plane_x = -1;
		sv->map.plane_y = 0;
	}
}

static void		set_dir_and_plane_ea_we(t_game *sv, int j, int i)
{
	if (sv->map.map_array[j] == 'W')
	{
		sv->map.dir_x = -1;
		sv->map.dir_y = 0;
		sv->map.plane_x = 0;
		sv->map.plane_y = -1;
	}
	else if (sv->map.map_array[j] == 'E')
	{
		sv->map.dir_x = 1;
		sv->map.dir_y = 0;
		sv->map.plane_x = 0;
		sv->map.plane_y = 1;
	}
}

void			set_player_vectors(t_game *sv, int j, int i)
{
//	sv->map.player_num = j;
	sv->map.pos_x = (double)i + 0.5;
	sv->map.pos_y = (((double)j - i) / sv->map.max_len) + 0.5;
	if (sv->map.map_array[j] == 'N' || sv->map.map_array[j] == 'S')
		set_dir_and_plane_no_so(sv, j, i);
	else
		set_dir_and_plane_ea_we(sv, j, i);
	sv->map.map_array[j] = '0';
	sv->map.plane_x *= FOV;
	sv->map.plane_y *= FOV;
}
