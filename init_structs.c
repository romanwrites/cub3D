/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 03:56:18 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/12 03:57:00 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void				init_map(t_conf *map)
{
	map->res_w = 0;
	map->res_h = 0;
	map->no_path = NULL;
	map->so_path = NULL;
	map->we_path = NULL;
	map->ea_path = NULL;
	map->s_path = NULL;
	map->floor_rgb[0] = 0;
	map->floor_rgb[1] = 0;
	map->floor_rgb[2] = 0;
	map->ceiling_rgb[0] = 0;
	map->ceiling_rgb[1] = 0;
	map->ceiling_rgb[2] = 0;
	map->player_direction = 0;
	map->map_cols = 0;
	map->map_rows = 0;
	map->map_arr = NULL;
}

static void		init_keys(t_game *sv)
{
	sv->keys.w = 0;
	sv->keys.a = 0;
	sv->keys.s = 0;
	sv->keys.d = 0;
	sv->keys.left = 0;
	sv->keys.right = 0;
}


static void		init_img(t_game *sv)
{
	sv->img.img = NULL;
	sv->img.addr = NULL;
	sv->img.bits_per_pixel = 0;
	sv->img.line_length = 0;
	sv->img.endian = 0;
}

void		init_game(t_game *sv)
{
	sv->head = NULL;
	sv->lst = NULL;
	sv->mlx = NULL;
	sv->win = NULL;
	init_img(sv);
	init_map(&sv->map);
	init_keys(sv);
    sv->sprites_count = 0;
	sv->map.f_color_parse = 0;
	sv->map.c_color_parse = 0;
}