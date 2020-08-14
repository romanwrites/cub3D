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
			if (sv->map.map_array[j] == '2')
				sv->map.player_num = j;
			i++;
			j++;
		}
		i = 0;
		sv->lst = sv->lst->next;
	}
	sv->map.map_array[j] = '\0';
}

//void draw_rectangle(std::vector<uint32_t> &img, const size_t img_w, const size_t img_h, const size_t x, const size_t y, const size_t w, const size_t h, const uint32_t color)
//{
//	for (size_t i=0; i<w; i++)
//	{
//		for (size_t j=0; j<h; j++)
//		{
//			size_t cx = x+i;
//			size_t cy = y+j;
//			if (cx>=img_w || cy>=img_h) continue; // no need to check negative values, (unsigned variables)
//			img[cx + cy*img_w] = color;
//		}
//	}
//}

void draw_rectangle(t_game *sv, const int img_w, const int img_h, const int x, const int y, const int w, const int h, int color)
{
	for (int i=0; i<w; i++)
	{
		for (int j=0; j<h; j++)
		{
			size_t cx = x+i;
			size_t cy = y+j;
			if (cx >= img_w || cy >= img_h) continue; // no need to check negative values, (unsigned variables)
			sv->img.addr[cx + cy*img_w] = color;
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

	double player_x = 3.456; // player x position
	double player_y = 2.345; // player y position
	double player_a = 1.523; // player view direction
	const double fov = M_PI/3.; // field of view

	const int rect_w = sv->map.res_w / (map_w * 2);
	const int rect_h = sv->map.res_h / map_h;

	while (i < map_h)
	{
		while (j < map_w)
		{
			if (sv->map.map_array[i+j*map_w] == '0')
			{
				j++;
				continue ;
			}

			rect_x = i * rect_w;
			rect_y = j * rect_h;
			draw_rectangle(sv, sv->map.res_w, sv->map.res_h, rect_x, rect_y, rect_w, rect_h, create_trgb(0, 0, 255, 255));
//			mlx_put_image_to_window(sv->mlx, sv->win, sv->img.img, 0, 0);
			j++;
		}
		j = 0;
		i++;
	}

	for (size_t i=0; i < (sv->map.res_w / 2); i++)
	{ // draw the visibility cone AND the "3D" view
		double angle = player_a-fov/2 + fov * i / ((double)(sv->map.res_w / 2));
		for (double t=0; t<20; t+=.05)
		{
			double cx = player_x + t * cos(angle);
			double cy = player_y + t * sin(angle);

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

