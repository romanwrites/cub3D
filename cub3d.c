/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 23:01:03 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/01 14:39:39 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_frame(t_game *sv)
{
	create_texture_imgs(sv);
	create_sprite_img(sv);
	cast_frame(sv);
}

void		handle_save(t_game *sv, char **argv)
{
	parse_args(3, argv[1], argv[2]);
	init_game(sv);
	read_map(open(argv[1], O_RDONLY), sv);
	check_map_params(sv);
	create_map_array(sv);
	check_res(sv);
	ft_my_lstclear(&sv->lst, free_lst_content);
	set_sprites_coordinates(sv);
	ft_alloc_check((sv->mlx = mlx_init()));
	sv->img.img = mlx_new_image(sv->mlx, sv->map.res_w, sv->map.res_h);
	ft_alloc_check(sv->img.img);
	sv->img.addr = mlx_get_data_addr(sv->img.img, &sv->img.bits_per_pixel, \
									&sv->img.line_length, &sv->img.endian);
	sv->filename = argv[1];
	sv->filename[ft_strlen(sv->filename) - 4] = '\0';
	draw_frame(sv);
	save_screenshot(sv, sv->filename);
	mlx_destroy_image(sv->mlx, sv->img.img);
	exit(0);
}

void		init_engine_parts(t_game *sv, char **argv)
{
	init_game(sv);
	read_map(open(argv[1], O_RDONLY), sv);
	check_map_params(sv);
	sv->filename = argv[1];
	sv->filename[ft_strlen(sv->filename) - 4] = '\0';
	if (sv->checklist.m == 1)
		create_map_array(sv);
	if (!(is_valid_map_file(&sv->checklist)))
		exit_with_err_msg("Map file is incorrect.");
	ft_my_lstclear(&sv->head, free_lst_content);
	sv->head = NULL;
	set_sprites_coordinates(sv);
	ft_alloc_check((sv->mlx = mlx_init()));
}

void		start_game(t_game *sv, char **argv)
{
	parse_args(2, argv[1], NULL);
	init_engine_parts(sv, argv);
	sv->win = mlx_new_window(sv->mlx, sv->map.res_w, \
							sv->map.res_h, sv->filename);
	ft_alloc_check(sv->win);
	sv->img.img = mlx_new_image(sv->mlx, sv->map.res_w, sv->map.res_h);
	ft_alloc_check(sv->img.img);
	sv->img.addr = mlx_get_data_addr(sv->img.img, &sv->img.bits_per_pixel, \
									&sv->img.line_length, &sv->img.endian);
	draw_frame(sv);
	mlx_put_image_to_window(sv->mlx, sv->win, sv->img.img, 0, 0);
	mlx_destroy_image(sv->mlx, sv->img.img);
	mlx_loop_hook(sv->mlx, render_frame, sv);
	mlx_hook(sv->win, KEY_PRESS, KEY_PRESS_MASK, press_key, sv);
	mlx_hook(sv->win, KEY_RELEASE, KEY_RELEASE_MASK, release_key, sv);
	mlx_hook(sv->win, 17, 1L << 17, ft_close, sv);
	mlx_loop(sv->mlx);
}

int			main(int argc, char **argv)
{
	t_game	sv;

	if (argc == 1)
		exit_with_err_msg("No arguments passed. Pass map.cub argument.");
	if (argc == 3)
		handle_save(&sv, argv);
	else if (argc == 2)
		start_game(&sv, argv);
	else
		exit_with_err_msg("Too many args. Pass only *.cub and --save.");
	return (0);
}
