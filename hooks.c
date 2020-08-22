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

int x = 0;

void	ft_put_map_line(char *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
	write(1, "|\n", 2);
}

double incr_a = 0;
double increase_a_coefficient_12 = 2 * M_PI / 12;
double incr_xy = 0;

void 		ft_event(int key, t_game *sv) // pass struct
{
	unsigned int colours[] = {0, 0, 0, 0};

	double frameTime = 1;
	double moveSpeed = 0.3; //the constant value is in squares/second
	double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

	printf("key: %d\n", key);



	if (key == W)
	{
		int mx_x, mx_y, my_x, my_y;
		mx_x = (int)((int)sv->map.pos_x + sv->map.dir_x * moveSpeed);
		mx_y = (int)sv->map.pos_y;
		my_x = (int)sv->map.pos_x;
		my_y = (int)((int)sv->map.pos_y + sv->map.dir_y * moveSpeed);
		if (sv->map.map_array[mx_x + mx_y * sv->map.max_len] == '0')
			sv->map.pos_x += sv->map.dir_x * moveSpeed;
		if (sv->map.map_array[my_x + my_y * sv->map.max_len] == '0')
			sv->map.pos_y += sv->map.dir_y * moveSpeed;

//		draw_black_screen(sv, sv->map.res_w, sv->map.res_h, create_trgb(0, 0, 0, 0));
		mlx_destroy_image(sv->mlx, sv->img.img);
		casting_frame(sv);
		mlx_put_image_to_window(sv->mlx, sv->win, sv->img.img, 0, 0);



//		if(sv->map.map_array[(int)sv->map.pos_x + sv->map.dir_x * moveSpeed][(int)sv->map.pos_y] == '0') sv->map.pos_x += sv->map.dir_x * moveSpeed;
//		if(sv->map.map_array[(int)sv->map.pos_x][(int)sv->map.pos_y + sv->map.dir_y * moveSpeed] == '0') sv->map.pos_y += sv->map.dir_y * moveSpeed;

//		if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
//		if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
	}
	if (key == S)
	{
		int mx_x, mx_y, my_x, my_y;
		mx_x = (int) ((int) sv->map.pos_x - sv->map.dir_x * moveSpeed);
		mx_y = (int) sv->map.pos_y;
		my_x = (int) sv->map.pos_x;
		my_y = (int) ((int) sv->map.pos_y - sv->map.dir_y * moveSpeed);
		if (sv->map.map_array[mx_x + mx_y * sv->map.max_len] == '0')
			sv->map.pos_x -= sv->map.dir_x * moveSpeed;
		if (sv->map.map_array[my_x + my_y * sv->map.max_len] == '0')
			sv->map.pos_y -= sv->map.dir_y * moveSpeed;

//		draw_black_screen(sv, sv->map.res_w, sv->map.res_h, create_trgb(0, 0, 0, 0));
		mlx_destroy_image(sv->mlx, sv->img.img);
		casting_frame(sv);
		mlx_put_image_to_window(sv->mlx, sv->win, sv->img.img, 0, 0);
	}
	if (key == 3)
	{
//		colours[0] = 0;
//		colours[1] = 255;
//		colours[2] = 0;
//		colours[3] = 0;

        sv->player.player_x = 0 + incr_xy; // player x position
        sv->player.player_y = 0 + incr_xy; // player y position
        sv->player.player_a = 0;
        printf("player_a: %f, player_x: %f, player_y: %f\n", sv->player.player_a, sv->player.player_x, sv->player.player_y);
        incr_a += increase_a_coefficient_12;
        incr_xy += 1;

		mlx_destroy_image(sv->mlx, sv->img.img);
		draw_map(sv);

		mlx_put_image_to_window(sv->mlx, sv->win, sv->img.img, 0, 0);
	}
	if (key == 14)
	{
		casting_frame(sv);
//		x++;
//		for (int j = 0; j < 100; j++)
//		{
//			draw_line_bresenham(0, j, 100, j, create_trgb(0, 255, 0, 0), sv);
//		}
//		draw_line_bresenham(0, 0, 100, 0, create_trgb(0, 255, 0, 0), sv);
		mlx_put_image_to_window(sv->mlx, sv->win, sv->img.img, 0, 0);
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
