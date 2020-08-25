/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 01:04:50 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/05 01:08:40 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		my_mlx_pixel_put(t_game *sv, int x, int y, unsigned int color)
{
	unsigned int *dst;
	dst = sv->img.addr + (y * sv->img.line_length + x * (sv->img.bits_per_pixel / 8)); //data->addr массив пикселей. Массив чаров. по 4. имиках может скинуть формулу
	*(unsigned int*)dst = color;
}

void		draw_line_bresenham(int x0, int y0, int x1, int y1, unsigned int colour, t_game *sv)
{
	int		delta_x;
	int		delta_y;
	int 	delta_x_abs;
	int 	delta_y_abs;
//	unsigned int 	colour = create_trgb(colours[0], colours[1], colours[2], colours[3]);
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

