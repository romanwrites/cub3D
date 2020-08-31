/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all_txt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 16:25:45 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/31 16:26:30 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				draw_no_txt(t_game *sv)
{
	int				texture_pixel;
	int				y;

	y = sv->draw.draw_start;
	sv->map.tex_x = (int)(sv->map.wall_x * (double)sv->map.no_w);
	if (sv->map.side == 1 && sv->map.ray_dir_y < 0)
		sv->map.tex_x = sv->map.no_w - sv->map.tex_x - 1;
	sv->map.step = 1.0 * sv->map.no_h / sv->map.line_height;
	sv->map.tex_pos = (sv->draw.draw_start - sv->map.res_h / 2 + \
						sv->map.line_height / 2) * sv->map.step;
	while (y < sv->draw.draw_end)
	{
		sv->map.tex_y = (int)sv->map.tex_pos & (sv->map.no_h - 1);
		sv->map.tex_pos += sv->map.step;
		texture_pixel = get_pixel(&sv->north, sv->map.tex_x, sv->map.tex_y);
		my_mlx_pixel_put(sv, sv->map.x, y, \
					add_shade(0.2, texture_pixel));
		y++;
	}
}

void				draw_so_txt(t_game *sv)
{
	int				texture_pixel;
	int				y;

	y = sv->draw.draw_start;
	sv->map.tex_x = (int)(sv->map.wall_x * (double)sv->map.so_w);
	if (sv->map.side == 1 && sv->map.ray_dir_y < 0)
		sv->map.tex_x = sv->map.so_w - sv->map.tex_x - 1;
	sv->map.step = 1.0 * sv->map.so_h / sv->map.line_height;
	sv->map.tex_pos = (sv->draw.draw_start - sv->map.res_h / 2 + \
						sv->map.line_height / 2) * sv->map.step;
	while (y < sv->draw.draw_end)
	{
		sv->map.tex_y = (int)sv->map.tex_pos & (sv->map.so_h - 1);
		sv->map.tex_pos += sv->map.step;
		texture_pixel = get_pixel(&sv->south, sv->map.tex_x, sv->map.tex_y);
		my_mlx_pixel_put(sv, sv->map.x, y, \
					add_shade(0.4, texture_pixel));
		y++;
	}
}

void				draw_ea_txt(t_game *sv)
{
	int				texture_pixel;
	int				y;

	y = sv->draw.draw_start;
	sv->map.tex_x = (int)(sv->map.wall_x * (double)sv->map.ea_w);
	if (sv->map.side == 0 && sv->map.ray_dir_x > 0)
		sv->map.tex_x = sv->map.no_w - sv->map.tex_x - 1;
	sv->map.step = 1.0 * sv->map.ea_h / sv->map.line_height;
	sv->map.tex_pos = (sv->draw.draw_start - sv->map.res_h / 2 + \
						sv->map.line_height / 2) * sv->map.step;
	while (y < sv->draw.draw_end)
	{
		sv->map.tex_y = (int)sv->map.tex_pos & (sv->map.ea_h - 1);
		sv->map.tex_pos += sv->map.step;
		texture_pixel = get_pixel(&sv->east, sv->map.tex_x, sv->map.tex_y);
		my_mlx_pixel_put(sv, sv->map.x, y, texture_pixel);
		y++;
	}
}

void				draw_we_txt(t_game *sv)
{
	int				texture_pixel;
	int				y;

	y = sv->draw.draw_start;
	sv->map.tex_x = (int)(sv->map.wall_x * (double)sv->map.we_w);
	if (sv->map.side == 0 && sv->map.ray_dir_x > 0)
		sv->map.tex_x = sv->map.no_w - sv->map.tex_x - 1;
	sv->map.step = 1.0 * sv->map.we_h / sv->map.line_height;
	sv->map.tex_pos = (sv->draw.draw_start - sv->map.res_h / 2 + \
						sv->map.line_height / 2) * sv->map.step;
	while (y < sv->draw.draw_end)
	{
		sv->map.tex_y = (int)sv->map.tex_pos & (sv->map.we_h - 1);
		sv->map.tex_pos += sv->map.step;
		texture_pixel = get_pixel(&sv->west, sv->map.tex_x, sv->map.tex_y);
		my_mlx_pixel_put(sv, sv->map.x, y, texture_pixel);
		y++;
	}
}

void				draw_all_txt(t_game *sv)
{
	if (sv->map.side == 1 && sv->map.step_y < 0)
	{
		draw_no_txt(sv);
	}
	else if (sv->map.side == 1 && sv->map.step_y > 0)
	{
		draw_so_txt(sv);
	}
	else if (sv->map.side == 0 && sv->map.step_x < 0)
	{
		draw_ea_txt(sv);
	}
	else if (sv->map.side == 0 && sv->map.step_x > 0)
	{
		draw_we_txt(sv);
	}
}
