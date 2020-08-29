/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 20:49:18 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/29 20:49:21 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		create_trgb(unsigned int t, unsigned int r, \
								unsigned int g, unsigned int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void		my_mlx_pixel_put(t_game *sv, int x, int y, unsigned int color)
{
	int *dst;
	dst = (void *)sv->img.addr + (y * sv->img.line_length + x * (sv->img.bits_per_pixel / 8));
	*(int*)dst = color;
}

int	get_pixel(t_data *img, int x, int y)
{
	int *dst;
	int	color;
	dst = (void *)img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(int*)dst;
	return (color);
}

int		add_shade(double distance, unsigned int color)
{
	int	transparency;
	int	red;
	int	green;
	int	blue;

	transparency = color & 0xFF000000;
	red = color & 0x00FF0000;
	green = color & 0x0000FF00;
	blue = color & 0x000000FF;

	red = (red >> 16) * (1 - distance);
	green = (green >> 8) * (1 - distance);
	blue = blue * (1 - distance);

	red = red << 16;
	green = green << 8;
	return (transparency | red | green | blue);
}