/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 03:24:11 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/12 03:24:35 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		set_player_vectors(t_game *sv, int j, int i)
{
	sv->map.player_num = j;
	sv->map.pos_x = (double)i + 0.5; // не позволять сдвинуться внутрь стены
	sv->map.pos_y = (((double)j - i) / sv->map.max_len) + 0.5;
	if (sv->map.map_array[j] == 'N')
	{
		sv->map.dir_x = 0;
		sv->map.dir_y = -1;
		sv->map.plane_x = 1;
		sv->map.plane_y = 0;
	}
	else if (sv->map.map_array[j] == 'S')
	{
		sv->map.dir_x = 0;
		sv->map.dir_y = 1;
		sv->map.plane_x = -1;
		sv->map.plane_y = 0;
	}
	else if (sv->map.map_array[j] == 'W')
	{
		sv->map.dir_x = -1;
		sv->map.dir_y = 0;
		sv->map.plane_x = 0;
		sv->map.plane_y = -1;
	}
	else if (sv->map.map_array[j] == 'E')
	{
		sv->map.dir_x = 1;
		sv->map.dir_y = 0;
		sv->map.plane_x = 0;
		sv->map.plane_y = 1;
	}
	sv->map.map_array[j] = '0';
	sv->map.plane_x *= tan(80/2 * M_PI/180); // FOV // можно просто значение написать, можно задефайнить фов
	sv->map.plane_y *= tan(80/2 * M_PI/180);
	printf ("\nPOSITION-------------------------\nx: %f, y: %f, dir_x: %f, dir_y: %f\n\n", sv->map.pos_x,sv->map.pos_y,sv->map.dir_x,	sv->map.dir_y);
}

void		set_plane_and_time(t_game *sv)
{
//	sv->map.plane_x = 0; //   // всегда должны быть перпендикулярны вектору направления
//	sv->map.plane_y = 1; //the 2d raycaster version of camera plane
	// потом этот вектор буду вращать с вектором направления      //


	sv->map.time = 0; //time of current frame
	sv->map.old_time = 0;; //time of previous frame
}

void		casting_frame(t_game *sv)
{
	unsigned int color;

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
		if(draw_start < 0)draw_start = 0;
		int draw_end = line_height / 2 + sv->map.res_h / 2;
		if(draw_end >= sv->map.res_h)draw_end = sv->map.res_h - 1;

		//give x and y sides different brightness
//		if (side == 1)
//		{
//			color = color / 2;
//		}

		//draw the pixels of the stripe as a vertical line
		draw_line_bresenham(x, draw_start, x, draw_end, color, sv);
	}
}

void		create_map_array(t_game *sv)
{
	int		i;
	int 	j;

	i = 0;
	j = 0;
	if (!(sv->map.map_array = ft_calloc(1, sv->map.map_rows * sv->map.map_cols + 1)))
		ft_error_close(ERR_MALLOC);
	while (sv->lst)
	{
		while (((char *)sv->lst->content)[i])
		{
			sv->map.map_array[j] = ((char *)sv->lst->content)[i];
			if (sv->map.map_array[j] == 'N' || sv->map.map_array[j] == 'S' || \
				sv->map.map_array[j] == 'W' || sv->map.map_array[j] == 'E')
			{
				set_player_vectors(sv, j, i);
			}
			i++;
			j++;
		}
		i = 0;
		sv->lst = sv->lst->next;
	}
	sv->map.map_array[j] = '\0';
	set_plane_and_time(sv);
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

