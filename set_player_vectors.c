/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_vectors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:50:41 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/30 16:22:34 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		set_dir_and_plane_no_so(t_game *sv, int j)
{
	if (sv->map.map_arr[j] == 'N')
	{
		sv->map.dir_x = 0;
		sv->map.dir_y = -0.1;
		sv->map.plane_x = 0.1;
		sv->map.plane_y = 0;
	}
	else if (sv->map.map_arr[j] == 'S')
	{
		sv->map.dir_x = 0;
		sv->map.dir_y = 1;
		sv->map.plane_x = -1;
		sv->map.plane_y = 0;
	}
}

static void		set_dir_and_plane_ea_we(t_game *sv, int j)
{
	if (sv->map.map_arr[j] == 'W')
	{
		sv->map.dir_x = -1;
		sv->map.dir_y = 0;
		sv->map.plane_x = 0;
		sv->map.plane_y = -1;
	}
	else if (sv->map.map_arr[j] == 'E')
	{
		sv->map.dir_x = 1;
		sv->map.dir_y = 0;
		sv->map.plane_x = 0;
		sv->map.plane_y = 1;
	}
}

void			set_player_vectors(t_game *sv, int j, int i)
{
	sv->map.pos_x = (double)i + 0.5;
	sv->map.pos_y = (((double)j - i) / sv->map.max_len) + 0.5;
	if (sv->map.map_arr[j] == 'N' || sv->map.map_arr[j] == 'S')
		set_dir_and_plane_no_so(sv, j);
	else
		set_dir_and_plane_ea_we(sv, j);
	sv->checklist.player += 1;
	sv->map.map_arr[j] = '0';
	sv->map.plane_x *= FOV;
	sv->map.plane_y *= FOV;
}
