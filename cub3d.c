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

int			main(int argc, char **argv)
{
	t_game	sv;
	char	*filename;
	if (argc == 1)
		ft_error_close(ERR_ARGC_MIN);
	else if (argc == 2)
	{
		printf("filename: %s\n", argv[1]);
		if (parse_args(2, argv[1], NULL))
		{
			init_game(&sv);
			read_map(open(argv[1], O_RDONLY), &sv);
			printf("filename: %s\n", argv[1]);
		}
//		ft_my_lstiter(sv.head, (void *)ft_put_map_line);  //дебаг печать
	}
	else if (argc == 3)
		parse_args(3, argv[1], argv[2]);
	else
		ft_error_close(ERR_ARGC_MAX);
	filename = argv[1];
	filename[ft_strlen(filename) - 4] = '\0';

	printf("w: %d, h: %d\n", sv.map.res_w,sv.map.res_h);

	create_map_array(&sv);

	sv.mlx = mlx_init();
	sv.win = mlx_new_window(sv.mlx, sv.map.res_w, sv.map.res_h, filename);

	sv.img.img = mlx_new_image(sv.mlx, sv.map.res_w, sv.map.res_h);
	sv.img.addr = mlx_get_data_addr(sv.img.img, &sv.img.bits_per_pixel, &sv.img.line_length,
								 &sv.img.endian);


	casting_frame(&sv);
	mlx_put_image_to_window(sv.mlx, sv.win, sv.img.img, 0, 0);
	mlx_destroy_image(sv.mlx, sv.img.img);

//	casting_frame(&sv);
//	mlx_put_image_to_window(&sv.mlx, &sv.win, &sv.img.img, 0, 0);

	printf("bits_per_pixel: %d, line_length %%d: %d, line_length %%u: %d, endian: %d\n", sv.img.bits_per_pixel, sv.img.line_length, sv.img.line_length, sv.img.endian);


//	mlx_hook(sv.win, 2, 1L<<0, ft_event, &sv);
//	printf("bits_per_pixel: %u, line_length: %u\n", vars->img.addr[0], vars->img.addr[1], vars->img.addr[2], vars->img.addr[3]);
//	printf("data.addr: %s\nlen data.addr: %zu\n", sv.img.addr, ft_strlen(sv.img.addr));
	printf("lines size: %d\n", sv.map.map_rows);
	printf("player: %d\n", sv.map.player_num);


//	mlx_key_hook(sv.win, ft_event, &sv);
	mlx_hook(sv.win, 2, 1L<<0, ft_event, &sv);//press
//	mlx_hook(sv.win, 3, 1L<<1, ft_event, &sv);//release
	mlx_hook(sv.win, 17, 1L << 17, ft_close, &sv);
	mlx_loop(sv.mlx);

	exit(0);
}
