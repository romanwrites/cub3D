/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 23:01:03 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/05 01:07:30 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 		ft_event(int key, t_game *vars) // можно передать только структуру
{
	unsigned int colours[] = {0, 255, 0, 0};

	printf("%d\n", key);
	if (key == 3)
		colours[2] = 255;
	if (key == 14)
		colours[2] = 0;
	draw_line_bresenham(10, 100, 200, 50, colours, &vars->img);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
//	write(1, "key pressed\n", 12);
}

int			main(int argc, char **argv)
{
	t_list	*map;
	map = NULL;
	t_game	sv;
	int		i = 0;
	int 	j = 0;
	unsigned int colours[] = {0, 255, 255, 0};
	unsigned int colour = 0x00000000;

	if (argc == 1)
		ft_error_close(ERR_ARGC_MIN);
	else if (argc == 2)
	{
		printf("filename: %s\n", argv[1]);
		if (parse_args(2, argv[1], NULL))
			read_map(open(argv[1], O_RDONLY), &map, &sv);
		ft_lstiter(map, (void *)ft_put_map_line);  //дебаг печать
	}
	else if (argc == 3)
		parse_args(3, argv[1], argv[2]);
	else
		ft_error_close(ERR_ARGC_MAX);

//
//
//	sv.mlx = mlx_init();
//	sv.win = mlx_new_window(sv.mlx, 800, 600, "cub3D");
//	sv.img.img = mlx_new_image(sv.mlx, 800, 600);
//	sv.img.addr = mlx_get_data_addr(sv.img.img, &sv.img.bits_per_pixel, &sv.img.line_length,
//								 &sv.img.endian);
////	mlx_key_hook(vars.win, ft_close, &vars);
//	mlx_hook(sv.win, 17, 1L << 17, ft_close, &sv);
//	mlx_hook(sv.win, 2, 1L<<0, ft_event, &sv);
//
////	draw_line_bresenham(10, 10, 200, 50, colours, &img);
////	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
////	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
////	mlx_loop_hook(vars.mlx, render_next_frame, YourStruct);
//	mlx_loop(sv.mlx);
	exit(0);
}
