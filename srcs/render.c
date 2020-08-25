/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 03:51:56 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/25 18:17:24 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		render_frame(t_game *sv)
{
	if (!sv->keys.w && !sv->keys.s && !sv->keys.a && !sv->keys.d && !sv->keys.right && !sv->keys.left)
		return (0);
	printf("LOLKEK------------------");
	check_buttons_state(sv);
	sv->img.img = mlx_new_image(sv->mlx, sv->map.res_w, sv->map.res_h);
	sv->img.addr = mlx_get_data_addr(sv->img.img, &sv->img.bits_per_pixel, &sv->img.line_length,
									 &sv->img.endian);
	cast_frame(sv);
	mlx_put_image_to_window(sv->mlx, sv->win, sv->img.img, 0, 0);
	mlx_destroy_image(sv->mlx, sv->img.img);
	return (0);
}
