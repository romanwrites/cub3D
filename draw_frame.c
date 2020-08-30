/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 19:34:35 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/29 19:34:37 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_ver_line(t_game *sv, int draw_start, int draw_end)
{
	int		y;

	y = draw_start;
	while (y <= draw_end)
	{
		my_mlx_pixel_put(sv, sv->draw.x, y, sv->draw.color);
		y++;
	}
}

void		draw_ceiling_and_floor(t_game *sv)
{
	sv->draw.color = sv->map.ceiling_color;
	draw_ver_line(sv, sv->draw.ceiling_y0, sv->draw.ceiling_y1);
	sv->draw.color = sv->map.floor_color;
	draw_ver_line(sv, sv->draw.floor_y0, sv->draw.floor_y1);
}