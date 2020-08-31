/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 16:31:39 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/31 16:31:53 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				calc_step_and_side_dst(t_game *sv)
{
	if (sv->map.ray_dir_x < 0)
	{
		sv->map.step_x = -1;
		sv->map.side_dist_x = (sv->map.pos_x - sv->map.map_x) * \
								sv->map.delta_dist_x;
	}
	else
	{
		sv->map.step_x = 1;
		sv->map.side_dist_x = (sv->map.map_x + 1.0 - sv->map.pos_x) * \
								sv->map.delta_dist_x;
	}
	if (sv->map.ray_dir_y < 0)
	{
		sv->map.step_y = -1;
		sv->map.side_dist_y = (sv->map.pos_y - sv->map.map_y) * \
								sv->map.delta_dist_y;
	}
	else
	{
		sv->map.step_y = 1;
		sv->map.side_dist_y = (sv->map.map_y + 1.0 - sv->map.pos_y) * \
								sv->map.delta_dist_y;
	}
}

void				calc_ray_pos_and_dir(t_game *sv)
{
	sv->map.camera_x = 2 * sv->map.x / (double)sv->map.res_w - 1;
	sv->map.ray_dir_x = sv->map.dir_x + sv->map.plane_x * sv->map.camera_x;
	sv->map.ray_dir_y = sv->map.dir_y + sv->map.plane_y * sv->map.camera_x;
	sv->map.map_x = (int)floor(sv->map.pos_x);
	sv->map.map_y = (int)floor(sv->map.pos_y);
	sv->map.delta_dist_x = fabs(1 / sv->map.ray_dir_x);
	sv->map.delta_dist_y = fabs(1 / sv->map.ray_dir_y);
}

void				calc_dist_projected_on_camera_direction(t_game *sv)
{
	if (sv->map.side == 0)
		sv->map.perp_wall_dist = (sv->map.map_x - sv->map.pos_x + \
								(1 - sv->map.step_x) / 2) / sv->map.ray_dir_x;
	else
		sv->map.perp_wall_dist = (sv->map.map_y - sv->map.pos_y + \
								(1 - sv->map.step_y) / 2) / sv->map.ray_dir_y;
}

void				calc_lowest_and_highest_pixels(t_game *sv)
{
	sv->draw.draw_start = -sv->map.line_height / 2 + sv->map.res_h / 2;
	if (sv->draw.draw_start < 0)
		sv->draw.draw_start = 0;
	sv->draw.draw_end = sv->map.line_height / 2 + sv->map.res_h / 2;
	if (sv->draw.draw_end >= sv->map.res_h)
		sv->draw.draw_end = sv->map.res_h - 1;
}

void				calc_wall_x(t_game *sv)
{
	if (sv->map.side == 0)
		sv->map.wall_x = sv->map.pos_y + sv->map.perp_wall_dist * \
												sv->map.ray_dir_y;
	else
		sv->map.wall_x = sv->map.pos_x + sv->map.perp_wall_dist * \
												sv->map.ray_dir_x;
	sv->map.wall_x -= floor((sv->map.wall_x));
}
