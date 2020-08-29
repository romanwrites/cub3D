/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 03:24:11 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/28 22:04:46 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


//arrays used to sort the sprites


//function used to sort the sprites
//sort the sprites based on distance
//void sortSprites(int* order, double* dist, int amount)
//{
//	std::vector<std::pair<double, int>> sprites(amount);
//	for(int i = 0; i < amount; i++) {
//		sprites[i].first = dist[i];
//		sprites[i].second = order[i];
//	}
//	std::sort(sprites.begin(), sprites.end());
//	// restore in reverse order to go from farthest to nearest
//	for(int i = 0; i < amount; i++) {
//		dist[i] = sprites[amount - i - 1].first;
//		order[i] = sprites[amount - i - 1].second;
//	}
//}


void		cast_frame(t_game *sv)
{
	int spriteOrder[sv->sprites_count];
	double spriteDistance[sv->sprites_count];
    //1D Zbuffer
    double ZBuffer[sv->map.res_w];

	unsigned int color;
	unsigned int texture_pixel;
	int texture_x;

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
		int draw_start = -line_height / 2 + sv->map.res_h / 2;
		if(draw_start < 0)
		    draw_start = 0;
		int draw_end = line_height / 2 + sv->map.res_h / 2;
		if(draw_end >= sv->map.res_h)
		    draw_end = sv->map.res_h - 1;

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
			double texPos = (draw_start - sv->map.res_h / 2 + line_height / 2) * step;
			for (int y = draw_start; y < draw_end; y++)
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
			double texPos = (draw_start - sv->map.res_h / 2 + line_height / 2) * step;
			for (int y = draw_start; y < draw_end; y++)
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
			double texPos = (draw_start - sv->map.res_h / 2 + line_height / 2) * step;
			for (int y = draw_start; y < draw_end; y++)
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
			double texPos = (draw_start - sv->map.res_h / 2 + line_height / 2) * step;
			for (int y = draw_start; y < draw_end; y++)
			{
				int texY = (int)texPos & (sv->map.we_h - 1);
				texPos += step;
				texture_pixel = get_pixel(&sv->west, texX, texY);
				my_mlx_pixel_put(sv, x, y, texture_pixel);
			}
		}
		draw_line_bresenham(x, 0, x, draw_start, sv->map.ceiling_color, sv);
		draw_line_bresenham(x, draw_end, x, sv->map.res_h - 1, sv->map.floor_color, sv);

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
//	sort sprites from far to close
	for(int i = 0; i < sv->sprites_count; i++)
	{
        sv->sprites_on_map[i].s_dist = ((sv->map.pos_x - sv->sprites_on_map[i].x) * (sv->map.pos_x - sv->sprites_on_map[i].x) + (sv->map.pos_y - sv->sprites_on_map[i].y) * (sv->map.pos_y - sv->sprites_on_map[i].y)); //sqrt not taken, unneeded
	}



    int j = 0;
	int i = 0;

    t_sprite	tmp;

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


void draw_rectangle(t_game *sv, const int img_w, const int img_h, const int x, const int y, const int w, const int h, int color)
{
	for (int i=0; i<w; i++)
	{
		for (int j=0; j<h; j++)
		{
			size_t cx = x+i;
			size_t cy = y+j;
			if (cx >= img_w || cy >= img_h) continue; // no need to check negative values, (unsigned variables)
			sv->img.addr[cx + cy * img_w] = color;
		}
	}
}

void    draw_black_screen(t_game *sv, int win_h, int win_w, int color)
{
    for (size_t j = 0; j<win_h; j++) { // fill the screen with color gradients
        for (size_t i = 0; i<win_w; i++) {
            uint8_t r = 255 * j / (float)win_h; // varies between 0 and 255 as j sweeps the vertical
            uint8_t g = 255 * i / (float)win_w; // varies between 0 and 255 as i sweeps the horizontal
            uint8_t b = 0;
            sv->img.addr[i+j*win_w] = color;
        }
    }
}

void		draw_map(t_game *sv)
{
	int 	i;
	int 	j;
	int 	map_w = 16;
	int 	map_h = 16;
	int		rect_x;
	int		rect_y;

	i = 0;
	j = 0;

////	double player_x = 3.456; // player x position
////	double player_y = 2.345; // player y position
////	double player_a = 1.523; // player view direction
//    sv->player.player_x = 3; // player x position
//    sv->player.player_y = 2; // player y position
//    sv->player.player_a = 1; // player view direction
	const double fov = M_PI/3.; // field of view

	const int rect_w = sv->map.res_w / (map_w * 2);
	const int rect_h = sv->map.res_h / map_h;

	while (i < map_h)
	{
		while (j < map_w)
		{
			if (sv->map.map_array[i + j * map_w] == '0')
			{
				j++;
				continue ;
			}

			rect_x = i * rect_w;
			rect_y = j * rect_h;
			draw_rectangle(sv, sv->map.res_w, sv->map.res_h, rect_x, rect_y, rect_w, rect_h, create_trgb(0, 0, 255, 255));
			mlx_put_image_to_window(sv->mlx, sv->win, sv->img.img, 0, 0);
			j++;
		}
		j = 0;
		i++;
	}

	for (size_t i=0; i < (sv->map.res_w / 2); i++)
	{ // draw the visibility cone AND the "3D" view
		double angle = sv->player.player_a-fov/2 + fov * i / ((double)(sv->map.res_w / 2));
		for (double t=0; t<20; t+=.05)
		{
			double cx = sv->player.player_x + t * cos(angle);
			double cy = sv->player.player_y + t * sin(angle);

			int pix_x = cx * rect_w;
			int pix_y = cy * rect_h;
			sv->img.addr[pix_x + pix_y * sv->map.res_w] = create_trgb(0, 255, 0, 0); // this draws the visibility cone

			if (sv->map.map_array[((int)cx) + ((int)cy) * map_w] != '0')
			{ // our ray touches a wall, so draw the vertical column to create an illusion of 3D
				size_t column_height = sv->map.res_h / t;
				draw_rectangle(sv, sv->map.res_w, sv->map.res_h, sv->map.res_w / 2 + i, sv->map.res_h / 2 - column_height / 2, 1, column_height, create_trgb(0, 255, 255, 0));
				break;
			}
		}
	}
}

