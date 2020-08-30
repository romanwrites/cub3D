/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 03:51:56 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/30 17:43:38 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void					print_frame_number()
{
	static long long int	frame_number;
	char					*frame;

	frame_number++;
	frame = ft_itoa_base(frame_number, 10);
	ft_alloc_check(frame);
	ft_putstr_fd("CURRENT FRAME NUMBER: ", 1);
	ft_putendl_fd(frame, 1);
	free(frame);
	frame = NULL;
}

int							render_frame(t_game *sv)
{
	if (!sv->keys.w && !sv->keys.s && !sv->keys.a && \
		!sv->keys.d && !sv->keys.right && !sv->keys.left)
		return (0);
	mlx_do_sync(sv->mlx);
	check_buttons_state(sv);
	sv->img.img = mlx_new_image(sv->mlx, sv->map.res_w, sv->map.res_h);
	ft_alloc_check(sv->img.img);
	sv->img.addr = mlx_get_data_addr(sv->img.img, &sv->img.bits_per_pixel, \
									&sv->img.line_length, &sv->img.endian);
	set_sprites_coordinates(sv);
	cast_frame(sv);
	mlx_put_image_to_window(sv->mlx, sv->win, sv->img.img, 0, 0);
	mlx_destroy_image(sv->mlx, sv->img.img);
	if (PRINT_FRAME_NUMBER)
		print_frame_number();
	return (0);
}
