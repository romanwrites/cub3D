/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trgb_colors_operations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 23:56:08 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/01 18:43:45 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int		add_shade(double distance, unsigned int color)
{
	unsigned int	transparency;
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

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

unsigned int		get_opposite(unsigned int color)
{
	unsigned int	transparency;
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	transparency = color & 0xFF000000;
	red = color & 0x00FF0000;
	green = color & 0x0000FF00;
	blue = color & 0x000000FF;

	red = red >> 16;
	green = green >> 8;
	
	red = 255 - red;
	green = 255 - green;
	blue = 255 - blue;
	return (transparency | red | green | blue);
}
