/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 03:24:11 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/31 18:24:44 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				draw_walls(t_game *sv)
{
	sv->map.z_buffer = malloc(sizeof(double) * sv->map.res_w);
	ft_alloc_check(sv->map.z_buffer);
	sv->map.x = 0;
	while (sv->map.x < sv->map.res_w)
	{
		calc_ray_pos_and_dir(sv);
		sv->map.hit = 0;
		calc_step_and_side_dst(sv);
		perform_dda(sv);
		calc_dist_projected_on_camera_direction(sv);
		sv->map.line_height = (int)(sv->map.res_h / sv->map.perp_wall_dist);
		calc_lowest_and_highest_pixels(sv);
		calc_wall_x(sv);
		draw_all_txt(sv);
		draw_ceiling_and_floor(sv);
		sv->map.z_buffer[sv->map.x] = sv->map.perp_wall_dist;
		sv->map.x++;
	}
}

void				do_the_projection(t_game *sv)
{
	int				i;

	i = 0;
	while (i < sv->sprites_count)
	{
		translate_sprite_pos(sv, i);
		transform_sprite_wt_inv_camera_mtrix(sv);
		sv->map.v_move_screen = (int)(VMOVE / sv->map.transform_y);
		sv->map.sprite_height = \
					abs((int)(sv->map.res_h / (sv->map.transform_y))) / VDIV;
		calc_min_max_sprite_pixels(sv);
		calc_width_of_the_sprite(sv);
		loop_through_every_ver_sprite_on_the_screen(sv);
		i++;
	}
}

void				cast_frame(t_game *sv)
{
	draw_walls(sv);
	count_sprite_dst(sv);
	sort_sprites(sv);
	do_the_projection(sv);
	free(sv->map.z_buffer);
}
