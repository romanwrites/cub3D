/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 03:24:11 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/31 15:18:43 by mkristie         ###   ########.fr       */
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

void				perform_dda(t_game *sv)
{
	while (sv->map.hit == 0)
	{
		if (sv->map.side_dist_x < sv->map.side_dist_y)
		{
			sv->map.side_dist_x += sv->map.delta_dist_x;
			sv->map.map_x += sv->map.step_x;
			sv->map.side = 0;
		}
		else
		{
			sv->map.side_dist_y += sv->map.delta_dist_y;
			sv->map.map_y += sv->map.step_y;
			sv->map.side = 1;
		}
		if (sv->map.map_arr[sv->map.map_x + sv->map.map_y * sv->map.max_len] \
																	== '1')
			sv->map.hit = 1;
	}
}

void				calc_dist_projected_on_camera_direction(t_game *sv)
{
	//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
	if(sv->map.side == 0)
		sv->map.perp_wall_dist = (sv->map.map_x - sv->map.pos_x + \
								(1 - sv->map.step_x) / 2) / sv->map.ray_dir_x; //перпендикулярное расстояние от плоскости камеры до точки где ударился об стену. так избавляемся от фишая
	else
		sv->map.perp_wall_dist = (sv->map.map_y - sv->map.pos_y + \
								(1 - sv->map.step_y) / 2) / sv->map.ray_dir_y;
}

void				calc_lowest_and_highest_pixels(t_game *sv)
{
	//calculate lowest and highest pixel to fill in current stripe
	sv->draw.draw_start = -sv->map.line_height / 2 + sv->map.res_h / 2;
	if(sv->draw.draw_start < 0)
		sv->draw.draw_start = 0;
	sv->draw.draw_end = sv->map.line_height / 2 + sv->map.res_h / 2;
	if(sv->draw.draw_end >= sv->map.res_h)
		sv->draw.draw_end = sv->map.res_h - 1;
}

void				calc_wall_x(t_game *sv)
{
	//calculate value of wallX
	if (sv->map.side == 0)
		sv->map.wall_x = sv->map.pos_y + sv->map.perp_wall_dist * sv->map.ray_dir_y;
	else
		sv->map.wall_x = sv->map.pos_x + sv->map.perp_wall_dist * sv->map.ray_dir_x;
	sv->map.wall_x -= floor((sv->map.wall_x));
}

void				draw_no_txt(t_game *sv)
{
	int				texture_pixel;
	int				y;

	y = sv->draw.draw_start;
	sv->map.tex_x = (int)(sv->map.wall_x * (double)sv->map.no_w);
	if(sv->map.side == 1 && sv->map.ray_dir_y < 0)
		sv->map.tex_x = sv->map.no_w - sv->map.tex_x - 1;
	sv->map.step = 1.0 * sv->map.no_h / sv->map.line_height;
	sv->map.tex_pos = (sv->draw.draw_start - sv->map.res_h / 2 + \
						sv->map.line_height / 2) * sv->map.step;
	while (y < sv->draw.draw_end)
	{
		sv->map.tex_y = (int)sv->map.tex_pos & (sv->map.no_h - 1);
		sv->map.tex_pos += sv->map.step;
		texture_pixel = get_pixel(&sv->north, sv->map.tex_x, sv->map.tex_y);
		my_mlx_pixel_put(sv, sv->map.x, y, \
					add_shade(0.2, texture_pixel));
		y++;
	}
}

void				draw_so_txt(t_game *sv)
{
	int				texture_pixel;
	int				y;

	y = sv->draw.draw_start;
	sv->map.tex_x = (int)(sv->map.wall_x * (double)sv->map.so_w);
	if(sv->map.side == 1 && sv->map.ray_dir_y < 0)
		sv->map.tex_x = sv->map.so_w - sv->map.tex_x - 1;
	sv->map.step = 1.0 * sv->map.so_h / sv->map.line_height;
	sv->map.tex_pos = (sv->draw.draw_start - sv->map.res_h / 2 + \
						sv->map.line_height / 2) * sv->map.step;
	while (y < sv->draw.draw_end)
	{
		sv->map.tex_y = (int)sv->map.tex_pos & (sv->map.so_h - 1);
		sv->map.tex_pos += sv->map.step;
		texture_pixel = get_pixel(&sv->south, sv->map.tex_x, sv->map.tex_y);
		my_mlx_pixel_put(sv, sv->map.x, y, \
					add_shade(0.4, texture_pixel));
		y++;
	}
}

void				draw_ea_txt(t_game *sv)
{
	int				texture_pixel;
	int				y;

	y = sv->draw.draw_start;
	sv->map.tex_x = (int)(sv->map.wall_x * (double)sv->map.ea_w);
	if(sv->map.side == 0 && sv->map.ray_dir_x > 0)
		sv->map.tex_x = sv->map.no_w - sv->map.tex_x - 1;
	sv->map.step = 1.0 * sv->map.ea_h / sv->map.line_height;
	sv->map.tex_pos = (sv->draw.draw_start - sv->map.res_h / 2 + \
						sv->map.line_height / 2) * sv->map.step;
	while (y < sv->draw.draw_end)
	{
		sv->map.tex_y = (int)sv->map.tex_pos & (sv->map.ea_h - 1);
		sv->map.tex_pos += sv->map.step;
		texture_pixel = get_pixel(&sv->east, sv->map.tex_x, sv->map.tex_y);
		my_mlx_pixel_put(sv, sv->map.x, y, texture_pixel);
		y++;
	}
}

void				draw_we_txt(t_game *sv)
{
	int				texture_pixel;
	int				y;

	y = sv->draw.draw_start;
	sv->map.tex_x = (int)(sv->map.wall_x * (double)sv->map.we_w);
	if(sv->map.side == 0 && sv->map.ray_dir_x > 0)
		sv->map.tex_x = sv->map.no_w - sv->map.tex_x - 1;
	sv->map.step = 1.0 * sv->map.we_h / sv->map.line_height;
	sv->map.tex_pos = (sv->draw.draw_start - sv->map.res_h / 2 + sv->map.line_height / 2) * sv->map.step;
	while (y < sv->draw.draw_end)
	{
		sv->map.tex_y = (int)sv->map.tex_pos & (sv->map.we_h - 1);
		sv->map.tex_pos += sv->map.step;
		texture_pixel = get_pixel(&sv->west, sv->map.tex_x, sv->map.tex_y);
		my_mlx_pixel_put(sv, sv->map.x, y, texture_pixel);
		y++;
	}
}

void				draw_all_txt(t_game *sv)
{
	if (sv->map.side == 1 && sv->map.step_y < 0)
	{
		draw_no_txt(sv);
	}
	else if (sv->map.side == 1 && sv->map.step_y > 0)
	{
		draw_so_txt(sv);
	}
	else if (sv->map.side == 0 && sv->map.step_x < 0)
	{
		draw_ea_txt(sv);
	}
	else if (sv->map.side == 0 && sv->map.step_x > 0)
	{
		draw_we_txt(sv);
	}
}

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

void				cast_frame(t_game *sv)
{
	draw_walls(sv);

//	SPRITE CASTING
	count_sprite_dst(sv);
	sort_sprites(sv);

	//after sorting the sprites, do the projection and draw them
	int 			i;

	i = 0;
	while (i < sv->sprites_count)
	{
		//translate sprite position to relative to camera
		sv->map.sprite_x = sv->sprites_on_map[i].x - sv->map.pos_x;
		sv->map.sprite_y = sv->sprites_on_map[i].y - sv->map.pos_y;

		//transform sprite with the inverse camera matrix
		// [ sv->map.plane_x   sv->map.dir_x ] -1                                       [ sv->map.dir_y      -sv->map.dir_x ]
		// [               ]       =  1/(sv->map.plane_x*sv->map.dir_y-sv->map.dir_x*sv->map.plane_y) *   [                 ]
		// [ sv->map.plane_y   sv->map.dir_y ]                                          [ -sv->map.plane_y  sv->map.plane_x ]

		sv->map.inv_det = 1.0 / (sv->map.plane_x * sv->map.dir_y - sv->map.dir_x * sv->map.plane_y); //required for correct matrix multiplication

		sv->map.transform_x = sv->map.inv_det * (sv->map.dir_y * sv->map.sprite_x - sv->map.dir_x * sv->map.sprite_y);
		sv->map.transform_y = sv->map.inv_det * (-sv->map.plane_y * sv->map.sprite_x + sv->map.plane_x * sv->map.sprite_y); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		sv->map.sprite_screen_x = (int)((sv->map.res_w / 2) * (1 + sv->map.transform_x / sv->map.transform_y));

		//parameters for scaling and moving the sprites
		#define uDiv 1
		#define vDiv 1
		#define vMove 150.0
		sv->map.v_move_screen = (int)(vMove / sv->map.transform_y);

		//calculate height of the sprite on screen
		sv->map.sprite_height = abs((int)(sv->map.res_h / (sv->map.transform_y))) / vDiv; //using "sv->map.transform_y" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		sv->map.draw_start_y = -sv->map.sprite_height / 2 + sv->map.res_h / 2 + sv->map.v_move_screen;
		if(sv->map.draw_start_y < 0) sv->map.draw_start_y = 0;
		sv->map.draw_end_y = sv->map.sprite_height / 2 + sv->map.res_h / 2 + sv->map.v_move_screen;
		if(sv->map.draw_end_y >= sv->map.res_h) sv->map.draw_end_y = sv->map.res_h - 1;

		//calculate width of the sprite
		sv->map.sprite_width = abs( (int) (sv->map.res_h / (sv->map.transform_y))) / uDiv;
		sv->map.draw_start_x = -sv->map.sprite_width / 2 + sv->map.sprite_screen_x;
		if(sv->map.draw_start_x < 0) sv->map.draw_start_x = 0;
		sv->map.draw_end_x = sv->map.sprite_width / 2 + sv->map.sprite_screen_x;
		if(sv->map.draw_end_x >= sv->map.res_w) sv->map.draw_end_x = sv->map.res_w - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = sv->map.draw_start_x; stripe < sv->map.draw_end_x; stripe++)
		{
			sv->map.s_tex_x = (int)(256 * (stripe - (-sv->map.sprite_width / 2 + sv->map.sprite_screen_x)) * 64 / sv->map.sprite_width) / 256; //64=texWidth
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) z_buffer, with perpendicular distance
			if(sv->map.transform_y > 0 && stripe > 0 && stripe < sv->map.res_w && sv->map.transform_y < sv->map.z_buffer[stripe])
            {
                for(int y = sv->map.draw_start_y; y < sv->map.draw_end_y; y++) //for every pixel of the current stripe
                {
                    int d = (y-sv->map.v_move_screen) * 256 - sv->map.res_h * 128 + sv->map.sprite_height * 128; //256 and 128 factors to avoid floats
                    sv->map.s_tex_y = ((d * 64) / sv->map.sprite_height) / 256;								    //64 = texHeight
                    int sprite_pixel = get_pixel(&sv->sprite, sv->map.s_tex_x, sv->map.s_tex_y);
                    if((sprite_pixel & 0x00FFFFFF) != 0)
                        my_mlx_pixel_put(sv, stripe, y, sprite_pixel);
                }
            }
		}
		free(sv->map.z_buffer);
		i++;
	}
}
