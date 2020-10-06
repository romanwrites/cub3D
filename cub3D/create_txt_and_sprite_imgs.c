/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_txt_and_sprite_imgs.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 14:33:57 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/01 14:34:04 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		create_sprite_img(t_game *sv)
{
	sv->sprite.img = mlx_xpm_file_to_image(sv->mlx, sv->map.s_path, \
										&sv->map.sprite_w, &sv->map.sprite_h);
	ft_alloc_check(sv->sprite.img);
	sv->sprite.addr = mlx_get_data_addr(sv->sprite.img, \
						&sv->sprite.bits_per_pixel, &sv->sprite.line_length, \
														&sv->sprite.endian);
}

void		create_texture_imgs(t_game *sv)
{
	sv->north.img = mlx_xpm_file_to_image(sv->mlx, sv->map.no_path, \
											&sv->map.no_w, &sv->map.no_h);
	ft_alloc_check(sv->north.img);
	sv->north.addr = mlx_get_data_addr(sv->north.img, \
		&sv->north.bits_per_pixel, &sv->north.line_length, &sv->north.endian);
	sv->south.img = mlx_xpm_file_to_image(sv->mlx, sv->map.so_path, \
											&sv->map.so_w, &sv->map.so_h);
	ft_alloc_check(sv->south.img);
	sv->south.addr = mlx_get_data_addr(sv->south.img, \
		&sv->south.bits_per_pixel, &sv->south.line_length, &sv->south.endian);
	sv->east.img = mlx_xpm_file_to_image(sv->mlx, sv->map.ea_path, \
											&sv->map.ea_w, &sv->map.ea_h);
	ft_alloc_check(sv->east.img);
	sv->east.addr = mlx_get_data_addr(sv->east.img, &sv->east.bits_per_pixel, \
									&sv->east.line_length, &sv->east.endian);
	sv->west.img = mlx_xpm_file_to_image(sv->mlx, sv->map.we_path, \
											&sv->map.we_w, &sv->map.we_h);
	ft_alloc_check(sv->west.img);
	sv->west.addr = mlx_get_data_addr(sv->west.img, &sv->west.bits_per_pixel, \
								&sv->west.line_length, &sv->west.endian);
}
