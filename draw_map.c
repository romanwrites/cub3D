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


void		cast_frame(t_game *sv)
{
    double ZBuffer[sv->map.res_w];

	unsigned int color;
	unsigned int texture_pixel;

	for(int x = 0; x < sv->map.res_w; x++)
	{
		//calculate ray position and direction
		double camera_x = 2 * x / (double)sv->map.res_w - 1; //x-coordinate in camera space
		double ray_dir_x = sv->map.dir_x + sv->map.plane_x * camera_x; // calculate the direction of the ray
		double ray_dir_y = sv->map.dir_y + sv->map.plane_y * camera_x; // sum of the direction vector, and a part of the plane vector

		//which box of the map we're in
		int map_x = (int)floor(sv->map.pos_x);// флор зануляет дробную часть and
		int map_y = (int)floor(sv->map.pos_y);// return the largest integral value less than or equal to x.

		//length of ray from current position to next x or y-side
		double side_dist_x;
		double side_dist_y;

		//length of ray from one x or y-side to next x or y-side
		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);
		double perp_wall_dist; //нужно для избегания фишай эффекта

		//what direction to step in x or y-direction (either +1 or -1)
		int step_x;
		int step_y;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial side_dist
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (sv->map.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - sv->map.pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (sv->map.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - sv->map.pos_y) * delta_dist_y;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				// в зависимости от того куда ударился луч — отрисовать стену. Если ударялся в стену спереди или сзади
				// определять в какую сторону шагал луч. степ_х будет якорем какую сторону для сайда выбрать
				side = 0; // стороны 0 1 2 3 по сторонам. если луч шагал наверх?
				if (step_x < 0)
					color = create_trgb(0, 255, 0, 0) / 2; // EAST
				else
					color = create_trgb(0, 0, 255, 0) / 2; // WEST
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				// а здесь определять по step_y западная или восточная стена.
				// после сохранить эти же значения во всех остальных функциях
				// можно создать массив где хранятся текстуры и обращаться к текстуре по сайду
				// имеет значение только последний шаг который я делал до стены.
				side = 1;
				if (step_y < 0)
					color = create_trgb(0, 0, 0, 255); // NORTH
				else
					color = create_trgb(0, 200, 0, 200); // SOUTH
			}
			//Check if ray has hit a wall
			if(sv->map.map_array[map_x + map_y * sv->map.max_len] == '1')
				hit = 1; //map_array
		}

		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(side == 0)
			perp_wall_dist = (map_x - sv->map.pos_x + (1 - step_x) / 2) / ray_dir_x; //перпендикулярное расстояние от плоскости камеры до точки где ударился об стену. так избавляемся от фишая
		else
			perp_wall_dist = (map_y - sv->map.pos_y + (1 - step_y) / 2) / ray_dir_y;

		//Calculate height of line to draw on screen
		int line_height = (int)(sv->map.res_h / perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		sv->draw.draw_start = -line_height / 2 + sv->map.res_h / 2;
		if(sv->draw.draw_start < 0)
		    sv->draw.draw_start = 0;
		sv->draw.draw_end = line_height / 2 + sv->map.res_h / 2;
		if(sv->draw.draw_end >= sv->map.res_h)
		    sv->draw.draw_end = sv->map.res_h - 1;

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0)
			wallX = sv->map.pos_y + perp_wall_dist * ray_dir_y;
		else
			wallX = sv->map.pos_x + perp_wall_dist * ray_dir_x;
		wallX -= floor((wallX));

		int texX;
		// NORTH----------------------------------
		if (side == 1 && step_y < 0)
		{
			texX = (int)(wallX * (double)sv->map.no_w);
			if(side == 1 && ray_dir_y < 0)
				texX = sv->map.no_w - texX - 1;
			double step = 1.0 * sv->map.no_h / line_height;
			double texPos = (sv->draw.draw_start - sv->map.res_h / 2 + line_height / 2) * step;
			for (int y = sv->draw.draw_start; y < sv->draw.draw_end; y++)
			{
				int texY = (int)texPos & (sv->map.no_h - 1);
				texPos += step;
				texture_pixel = get_pixel(&sv->north, texX, texY);
				my_mlx_pixel_put(sv, x, y, add_shade(0.2, texture_pixel));
			}
		}
		// SOUTH----------------------------------
		else if (side == 1 && step_y > 0)
		{
			texX = (int)(wallX * (double)sv->map.so_w);
			if(side == 1 && ray_dir_y < 0)
				texX = sv->map.so_w - texX - 1;
			double step = 1.0 * sv->map.so_h / line_height;
			double texPos = (sv->draw.draw_start - sv->map.res_h / 2 + line_height / 2) * step;
			for (int y = sv->draw.draw_start; y < sv->draw.draw_end; y++)
			{
				int texY = (int)texPos & (sv->map.so_h - 1);
				texPos += step;
				texture_pixel = get_pixel(&sv->south, texX, texY);
				my_mlx_pixel_put(sv, x, y, add_shade(0.4, texture_pixel));
			}
		}
		// EAST----------------------------------
		else if (side == 0 && step_x < 0)
		{
			texX = (int)(wallX * (double)sv->map.ea_w);
			if(side == 0 && ray_dir_x > 0)
				texX = sv->map.no_w - texX - 1;
			double step = 1.0 * sv->map.ea_h / line_height;
			double texPos = (sv->draw.draw_start - sv->map.res_h / 2 + line_height / 2) * step;
			for (int y = sv->draw.draw_start; y < sv->draw.draw_end; y++)
			{
				int texY = (int)texPos & (sv->map.ea_h - 1);
				texPos += step;
				texture_pixel = get_pixel(&sv->east, texX, texY);
				my_mlx_pixel_put(sv, x, y, texture_pixel);
			}
		}
		// WEST----------------------------------
		else if (side == 0 && step_x > 0)
		{
			texX = (int)(wallX * (double)sv->map.we_w);
			if(side == 0 && ray_dir_x > 0)
				texX = sv->map.no_w - texX - 1;
			double step = 1.0 * sv->map.we_h / line_height;
			double texPos = (sv->draw.draw_start - sv->map.res_h / 2 + line_height / 2) * step;
			for (int y = sv->draw.draw_start; y < sv->draw.draw_end; y++)
			{
				int texY = (int)texPos & (sv->map.we_h - 1);
				texPos += step;
				texture_pixel = get_pixel(&sv->west, texX, texY);
				my_mlx_pixel_put(sv, x, y, texture_pixel);
			}
		}
		sv->draw.ceiling_y0 = 0;
		sv->draw.ceiling_y1 = sv->draw.draw_start;
		sv->draw.floor_y0 = sv->draw.draw_end;
		sv->draw.floor_y1 = sv->map.res_h - 1;
		sv->draw.x = x;
		draw_ceiling_and_floor(sv);
//		draw_line_bresenham(x, 0, x, sv->draw.draw_start, sv->map.ceiling_color, sv);
		
//		draw_floor(sv);
//		draw_line_bresenham(x, sv->draw.draw_end, x, sv->map.res_h - 1, sv->map.floor_color, sv);

        ZBuffer[x] = perp_wall_dist; // store the perpendicular distance of each vertical stripe in a 1D ZBuffer
        // чтобы понять что конкретная часть спрайта за стеной. Чтобы не отрисовать то, что находится дальше чем стена
	}
//
//	1: While raycasting the walls, store the perpendicular distance of each vertical stripe in a 1D ZBuffer
//	2: Calculate the distance of each sprite to the player
//	3: Use this distance to sort the sprites, from furthest away to closest to the camera
//	4: Project the sprite on the camera plane (in 2D): subtract the player position from the sprite position, then multiply the result with the inverse of the 2x2 camera matrix
//	5: Calculate the size of the sprite on the screen (both in x and y direction) by using the perpendicular distance
//	6: Draw the sprites vertical stripe by vertical stripe, don't draw the vertical stripe if the distance is further away than the 1D ZBuffer of the walls of the current stripe
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
			//4) ZBuffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < sv->map.res_w && transformY < ZBuffer[stripe])
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
