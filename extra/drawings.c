/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 01:04:50 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/29 19:25:30 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_player {
	double player_x; // player x position
	double player_y; // player y position
	double player_a;
}				t_player;

void		draw_line_bresenham(int x0, int y0, int x1, int y1, unsigned int colour, t_game *sv)
{
	int		delta_x;
	int		delta_y;
	int 	delta_x_abs;
	int 	delta_y_abs;
	int accretion = 0;

	delta_x = x1 - x0;
	delta_y = y1 - y0;
	delta_x_abs = abs(delta_x);
	delta_y_abs = abs(delta_y);

	if (delta_x_abs >= delta_y_abs)
	{
		int y = y0;
		const int direction = delta_y != 0 ? (delta_y > 0 ? 1 : -1) : 0;
		for (int x = x0; delta_x > 0 ? x <= x1 : x >= x1; delta_x > 0 ? x++ : x--)
		{
			my_mlx_pixel_put(sv, x, y, colour);
			accretion += delta_y_abs;
			if (accretion >= delta_x_abs)
			{
				accretion -= delta_x_abs;
				y += direction;
			}
		}
	}
	else
	{
		int x = x0;
		const int direction = delta_x != 0 ? (delta_x > 0 ? 1 : -1) : 0;
		for (int y = y0; delta_y > 0 ? y <= y1 : y >= y1; delta_y > 0 ? y++ : y--)
		{
			my_mlx_pixel_put(sv, x, y, colour);
			accretion += delta_x_abs;
			if (accretion >= delta_y_abs)
			{
				accretion -= delta_y_abs;
				y += direction;
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


