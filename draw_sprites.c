/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 19:13:54 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/31 18:25:10 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				draw_sprite_verline(t_game *sv, int stripe, int y)
{
	int				d;
	int				sprite_pixel;
	
	while (y < sv->map.draw_end_y)
	{
		d = (y - sv->map.v_move_screen) * 256 - sv->map.res_h * \
			128 + sv->map.sprite_height * 128;
		sv->map.s_tex_y = ((d * 64) / sv->map.sprite_height) / 256;
		sprite_pixel = \
			get_pixel(&sv->sprite, sv->map.s_tex_x, sv->map.s_tex_y);
		if ((sprite_pixel & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(sv, stripe, y, sprite_pixel);
		y++;
	}
}
void				loop_through_every_ver_sprite_on_the_screen(t_game *sv)
{
	int				stripe;
	int				y;
	
	stripe = sv->map.draw_start_x;
	y = sv->map.draw_start_y;
	while (stripe < sv->map.draw_end_x)
	{
		sv->map.s_tex_x = (int)(256 * (stripe - (-sv->map.sprite_width / \
			2 + sv->map.sprite_screen_x)) * 64 / sv->map.sprite_width) / 256;
		if (sv->map.transform_y > 0 && stripe > 0 && \
			stripe < sv->map.res_w && \
			sv->map.transform_y < sv->map.z_buffer[stripe])
		{
			draw_sprite_verline(sv, stripe, y);
		}
		stripe++;
	}
}

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
