/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 03:51:56 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/12 03:51:58 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_map_line(char *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
	write(1, "|\n", 2);
}

void 		ft_event(int key, t_game *sv) // pass struct
{
	unsigned int colours[] = {0, 0, 0, 0};

	printf("key: %d\n", key);
	if (key == 3)
	{
//		colours[0] = 0;
//		colours[1] = 255;
//		colours[2] = 0;
//		colours[3] = 0;
		draw_map(sv);
		mlx_put_image_to_window(sv->mlx, sv->win, sv->img.img, 0, 0);
	}
	if (key == 14)
	{
		colours[0] = 0;
		colours[1] = 0;
		colours[2] = 255;
		colours[3] = 0;
	}
	if (key == 53)
	{
		ft_close(key, sv);
	}
	if (key == 2)
	{
		colours[0] = 0;
		colours[1] = 0;
		colours[2] = 0;
		colours[3] = 255;
	}
//	else
//		return ;
//	for(int j = 0; j < 100; j++)
//	{
//		draw_line_bresenham(0, j, 100, j, colours, &sv->img);
//	}
//	draw_line_bresenham(0, 0, 100, 0, colours, &vars->img);
//	draw_map(sv);
//	for(int k = 1; k < 2700; k += 4)
//	{
////		printf("k = %d\nimg.addr[k]: %u, img.addr[k + 1]: %u\n", k, sv->img.addr[k],sv->img.addr[k + 1]);
//		sv->img.addr[k] = 0;
//		sv->img.addr[k + 1] = 200;
////		printf("NEW img.addr[k]: %u, img.addr[k + 1]: %u\n", sv->img.addr[k],sv->img.addr[k + 1]);
//
////		printf("blue: %u, green: %u, red: %u, transparency: %u\n", sv->img.addr[k-1], sv->img.addr[k], sv->img.addr[k+1], sv->img.addr[k+2]);
//	}
//	mlx_put_image_to_window(sv->mlx, sv->win, sv->img.img, 0, 0);

//	printf("line_length %%d: %d, line_length %%u: %d\n", (int)(sv->img.line_length), (unsigned int)(sv->img.line_length));
//	printf("blue: %u, green: %u, red: %u, transparency: %u\nbits_per_pixel: %d, line_length: %d, endian: %d\n", sv->img.addr[0], sv->img.addr[1], sv->img.addr[2], sv->img.addr[3], sv->img.bits_per_pixel, sv->img.line_length, sv->img.endian);
//	printf("data.addr: %s\nlen data.addr: %zu\n", vars->img.addr, ft_strlen(vars->img.addr));
//	for(int i = 0; i < 200; i += 4)
//	{
//		printf("blue: %u, green: %u, red: %u, transparency: %u\n", sv->img.addr[i], sv->img.addr[i+1], sv->img.addr[i+2], sv->img.addr[i-1]);
//	}
//	write(1, "key pressed\n", 12);

}
