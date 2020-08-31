/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites_calc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 18:25:28 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/31 18:29:31 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				translate_sprite_pos(t_game *sv, int i)
{
	sv->map.sprite_x = sv->sprites_on_map[i].x - sv->map.pos_x;
	sv->map.sprite_y = sv->sprites_on_map[i].y - sv->map.pos_y;
}

void				transform_sprite_wt_inv_camera_mtrix(t_game *sv)
{
	sv->map.inv_det = 1.0 / \
		(sv->map.plane_x * sv->map.dir_y - sv->map.dir_x * sv->map.plane_y);
	sv->map.transform_x = sv->map.inv_det * \
		(sv->map.dir_y * sv->map.sprite_x - sv->map.dir_x * sv->map.sprite_y);
	sv->map.transform_y = sv->map.inv_det * (-sv->map.plane_y * \
						sv->map.sprite_x + sv->map.plane_x * sv->map.sprite_y);
	sv->map.sprite_screen_x = (int)((sv->map.res_w / 2) * \
							(1 + sv->map.transform_x / sv->map.transform_y));
}

void				calc_min_max_sprite_pixels(t_game *sv)
{
	sv->map.draw_start_y = -sv->map.sprite_height / \
						2 + sv->map.res_h / 2 + sv->map.v_move_screen;
	if (sv->map.draw_start_y < 0)
		sv->map.draw_start_y = 0;
	sv->map.draw_end_y = sv->map.sprite_height / \
						2 + sv->map.res_h / 2 + sv->map.v_move_screen;
	if (sv->map.draw_end_y >= sv->map.res_h)
		sv->map.draw_end_y = sv->map.res_h - 1;
}

void				calc_width_of_the_sprite(t_game *sv)
{
	sv->map.sprite_width = \
					abs((int)(sv->map.res_h / (sv->map.transform_y))) / UDIV;
	sv->map.draw_start_x = -sv->map.sprite_width / 2 + sv->map.sprite_screen_x;
	if (sv->map.draw_start_x < 0)
		sv->map.draw_start_x = 0;
	sv->map.draw_end_x = sv->map.sprite_width / 2 + sv->map.sprite_screen_x;
	if (sv->map.draw_end_x >= sv->map.res_w)
		sv->map.draw_end_x = sv->map.res_w - 1;
}
