/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 19:13:54 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/29 19:14:48 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			sort_sprites(t_game *sv)
{
	int			i;
	int			j;
	t_sprite	tmp;

	j = 0;
	while (j < sv->sprites_count - 1)
	{
		i = 0;
		while (i < sv->sprites_count - j - 1)
		{
			if (sv->sprites_on_map[i].s_dist < sv->sprites_on_map[i + 1].s_dist)
			{
				tmp = sv->sprites_on_map[i];
				sv->sprites_on_map[i] = sv->sprites_on_map[i + 1];
				sv->sprites_on_map[i + 1] = tmp;
			}
			i++;
		}
		j++;
	}
}

void			count_sprite_dst(t_game *sv)
{
	int			i;

	i = 0;
	while (i < sv->sprites_count)
	{
		sv->sprites_on_map[i].s_dist = \
			((sv->map.pos_x - sv->sprites_on_map[i].x) * \
			(sv->map.pos_x - sv->sprites_on_map[i].x) + \
			(sv->map.pos_y - sv->sprites_on_map[i].y) * \
			(sv->map.pos_y - sv->sprites_on_map[i].y));
		i++;
	}
}
