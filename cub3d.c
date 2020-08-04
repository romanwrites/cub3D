/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 23:01:03 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/03 19:21:14 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void		draw_square(int i, int j, unsigned int *colours, t_data *img)
{
	unsigned int colour;

	while (i++ < 255)
	{
		while (j++ < 255)
		{
			my_mlx_pixel_put(img, j, i, colour);
		}
		j = 0;
		colours[1]--;
		colours[2]++;
		colours[3]++;
		colour = create_trgb(0, colours[1], colours[2], colours[3]);
	}
}

void		draw_circle(int i, int j, unsigned int *colours, t_data *img, int y)
{
	unsigned int	colour;
	int 			radius;
	// R - радиус, X1, Y1 - координаты центра
	int x = 0;
//	int y = ra;
	int x_mid, y_mid = 200;
	int delta = 1 - 2 * 100;
	int error = 0;
	colour = create_trgb(0, colours[1], colours[2], colours[3]);
	while (y >= 0)
	{
		my_mlx_pixel_put(img, x_mid + x, y_mid + y, colour);
		my_mlx_pixel_put(img, x_mid + x, y_mid - y, colour);
		my_mlx_pixel_put(img, x_mid - x, y_mid + y, colour);
		my_mlx_pixel_put(img, x_mid - x, y_mid - y, colour);
		error = 2 * (delta + y) - 1;
		if ((delta < 0) && (error <= 0))
		{
			delta += 2 * ++x + 1;
			continue;
		}
		if ((delta > 0) && (error > 0))
		{
			delta -= 2 * --y + 1;
			continue;
		}
		delta += 2 * (++x - --y);
	}
}

int			main(void)
{
	void    *mlx;
	void    *mlx_win;
	t_data  img;
	int		i = 0;
	int 	j = 0;
	unsigned int colours[] = {0, 255, 0, 0};
	unsigned int colour = 0x00000000;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 600, "cub3D");
	img.img = mlx_new_image(mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
//	draw_square(i, j, colours, &img);
	int r = 100;
	draw_circle(i, j, colours, &img, r);
//	my_mlx_pixel_put(&img, 0, 0, colour);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
