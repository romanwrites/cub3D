/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 03:24:11 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/30 16:22:50 by mkristie         ###   ########.fr       */
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
		if (sv->map.map_array[sv->map.map_x + sv->map.map_y * sv->map.max_len] \
																		== '1')
			sv->map.hit = 1;
	}
}

void				check_ray_dir(t_game *sv)
{
	int				color;
	int				texture_pixel;

	sv->map.z_buffer = malloc(sizeof(double) * sv->map.res_w);
	ft_alloc_check(sv->map.z_buffer);
	sv->map.x = 0;
	while (sv->map.x < sv->map.res_w)
	{
		calc_ray_pos_and_dir(sv);
		sv->map.hit = 0;
		calc_step_and_side_dst(sv);
		perform_dda(sv);

		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(sv->map.side == 0)
			sv->map.perp_wall_dist = (sv->map.map_x - sv->map.pos_x + (1 - sv->map.step_x) / 2) / sv->map.ray_dir_x; //перпендикулярное расстояние от плоскости камеры до точки где ударился об стену. так избавляемся от фишая
		else
			sv->map.perp_wall_dist = (sv->map.map_y - sv->map.pos_y + (1 - sv->map.step_y) / 2) / sv->map.ray_dir_y;

		//Calculate height of line to draw on screen
		int line_height = (int)(sv->map.res_h / sv->map.perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		sv->draw.draw_start = -line_height / 2 + sv->map.res_h / 2;
		if(sv->draw.draw_start < 0)
			sv->draw.draw_start = 0;
		sv->draw.draw_end = line_height / 2 + sv->map.res_h / 2;
		if(sv->draw.draw_end >= sv->map.res_h)
			sv->draw.draw_end = sv->map.res_h - 1;

		//calculate value of wallX
		double wallX; //where exactly the wall was sv->map.hit
		if (sv->map.side == 0)
			wallX = sv->map.pos_y + sv->map.perp_wall_dist * sv->map.ray_dir_y;
		else
			wallX = sv->map.pos_x + sv->map.perp_wall_dist * sv->map.ray_dir_x;
		wallX -= floor((wallX));

		int texX;
		// NORTH----------------------------------
		if (sv->map.side == 1 && sv->map.step_y < 0)
		{
			texX = (int)(wallX * (double)sv->map.no_w);
			if(sv->map.side == 1 && sv->map.ray_dir_y < 0)
				texX = sv->map.no_w - texX - 1;
			double step = 1.0 * sv->map.no_h / line_height;
			double texPos = (sv->draw.draw_start - sv->map.res_h / 2 + line_height / 2) * step;
			for (int y = sv->draw.draw_start; y < sv->draw.draw_end; y++)
			{
				int texY = (int)texPos & (sv->map.no_h - 1);
				texPos += step;
				texture_pixel = get_pixel(&sv->north, texX, texY);
				my_mlx_pixel_put(sv, sv->map.x, y, add_shade(0.2, texture_pixel));
			}
		}
			// SOUTH----------------------------------
		else if (sv->map.side == 1 && sv->map.step_y > 0)
		{
			texX = (int)(wallX * (double)sv->map.so_w);
			if(sv->map.side == 1 && sv->map.ray_dir_y < 0)
				texX = sv->map.so_w - texX - 1;
			double step = 1.0 * sv->map.so_h / line_height;
			double texPos = (sv->draw.draw_start - sv->map.res_h / 2 + line_height / 2) * step;
			for (int y = sv->draw.draw_start; y < sv->draw.draw_end; y++)
			{
				int texY = (int)texPos & (sv->map.so_h - 1);
				texPos += step;
				texture_pixel = get_pixel(&sv->south, texX, texY);
				my_mlx_pixel_put(sv, sv->map.x, y, add_shade(0.4, texture_pixel));
			}
		}
			// EAST----------------------------------
		else if (sv->map.side == 0 && sv->map.step_x < 0)
		{
			texX = (int)(wallX * (double)sv->map.ea_w);
			if(sv->map.side == 0 && sv->map.ray_dir_x > 0)
				texX = sv->map.no_w - texX - 1;
			double step = 1.0 * sv->map.ea_h / line_height;
			double texPos = (sv->draw.draw_start - sv->map.res_h / 2 + line_height / 2) * step;
			for (int y = sv->draw.draw_start; y < sv->draw.draw_end; y++)
			{
				int texY = (int)texPos & (sv->map.ea_h - 1);
				texPos += step;
				texture_pixel = get_pixel(&sv->east, texX, texY);
				my_mlx_pixel_put(sv, sv->map.x, y, texture_pixel);
			}
		}
			// WEST----------------------------------
		else if (sv->map.side == 0 && sv->map.step_x > 0)
		{
			texX = (int)(wallX * (double)sv->map.we_w);
			if(sv->map.side == 0 && sv->map.ray_dir_x > 0)
				texX = sv->map.no_w - texX - 1;
			double step = 1.0 * sv->map.we_h / line_height;
			double texPos = (sv->draw.draw_start - sv->map.res_h / 2 + line_height / 2) * step;
			for (int y = sv->draw.draw_start; y < sv->draw.draw_end; y++)
			{
				int texY = (int)texPos & (sv->map.we_h - 1);
				texPos += step;
				texture_pixel = get_pixel(&sv->west, texX, texY);
				my_mlx_pixel_put(sv, sv->map.x, y, texture_pixel);
			}
		}
		sv->draw.ceiling_y0 = 0;
		sv->draw.ceiling_y1 = sv->draw.draw_start;
		sv->draw.floor_y0 = sv->draw.draw_end;
		sv->draw.floor_y1 = sv->map.res_h - 1;
		sv->draw.x = sv->map.x;
		draw_ceiling_and_floor(sv);
//		draw_line_bresenham(x, 0, x, sv->draw.draw_start, sv->map.ceiling_color, sv);

//		draw_floor(sv);
//		draw_line_bresenham(x, sv->draw.draw_end, x, sv->map.res_h - 1, sv->map.floor_color, sv);

		sv->map.z_buffer[sv->map.x] = sv->map.perp_wall_dist; // store the perpendicular distance of each vertical stripe in a 1D z_buffer
		// чтобы понять что конкретная часть спрайта за стеной. Чтобы не отрисовать то, что находится дальше чем стена
		sv->map.x++;
	}
}


void				cast_frame(t_game *sv)
{
	check_ray_dir(sv);
//
//	1: While raycasting the walls, store the perpendicular distance of each vertical stripe in a 1D z_buffer
//	2: Calculate the distance of each sprite to the player
//	3: Use this distance to sort the sprites, from furthest away to closest to the camera
//	4: Project the sprite on the camera plane (in 2D): subtract the player position from the sprite position, then multiply the result with the inverse of the 2x2 camera matrix
//	5: Calculate the size of the sprite on the screen (both in x and y direction) by using the perpendicular distance
//	6: Draw the sprites vertical stripe by vertical stripe, don't draw the vertical stripe if the distance is further away than the 1D z_buffer of the walls of the current stripe
//	7: Draw the vertical stripe pixel by pixel, make sure there's an invisible color or all sprites would be rectangles



//	SPRITE CASTING
	count_sprite_dst(sv);
	sort_sprites(sv);

	//after sorting the sprites, do the projection and draw them
	for(int i = 0; i < sv->sprites_count; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = sv->sprites_on_map[i].x - sv->map.pos_x;
		double spriteY = sv->sprites_on_map[i].y - sv->map.pos_y;

		//transform sprite with the inverse camera matrix
		// [ sv->map.plane_x   sv->map.dir_x ] -1                                       [ sv->map.dir_y      -sv->map.dir_x ]
		// [               ]       =  1/(sv->map.plane_x*sv->map.dir_y-sv->map.dir_x*sv->map.plane_y) *   [                 ]
		// [ sv->map.plane_y   sv->map.dir_y ]                                          [ -sv->map.plane_y  sv->map.plane_x ]

		double invDet = 1.0 / (sv->map.plane_x * sv->map.dir_y - sv->map.dir_x * sv->map.plane_y); //required for correct matrix multiplication

		double transformX = invDet * (sv->map.dir_y * spriteX - sv->map.dir_x * spriteY);
		double transformY = invDet * (-sv->map.plane_y * spriteX + sv->map.plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spriteScreenX = (int)((sv->map.res_w / 2) * (1 + transformX / transformY));

		//parameters for scaling and moving the sprites
		#define uDiv 1
		#define vDiv 1
		#define vMove 150.0
		int vMoveScreen = (int)(vMove / transformY);

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(sv->map.res_h / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + sv->map.res_h / 2 + vMoveScreen;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + sv->map.res_h / 2 + vMoveScreen;
		if(drawEndY >= sv->map.res_h) drawEndY = sv->map.res_h - 1;

		//calculate width of the sprite
		int spriteWidth = abs( (int) (sv->map.res_h / (transformY))) / uDiv;
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= sv->map.res_w) drawEndX = sv->map.res_w - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 64 / spriteWidth) / 256; //64=texWidth
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) z_buffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < sv->map.res_w && transformY < sv->map.z_buffer[stripe])
            {
                for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
                {
                    int d = (y-vMoveScreen) * 256 - sv->map.res_h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
                    int texY = ((d * 64) / spriteHeight) / 256;								    //64 = texHeight
                    int sprite_pixel = get_pixel(&sv->sprite, texX, texY);
                    if((sprite_pixel & 0x00FFFFFF) != 0)
                        my_mlx_pixel_put(sv, stripe, y, sprite_pixel);
                }
            }
		}
	}
}
