/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:15:26 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/01 20:07:39 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			exit_with_err_msg(char *str)
{
	ft_putendl_fd("Error!", 2);
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

void			ft_error_close(int error_code)
{
	if (error_code == ERR_ARGC_MIN)
		write(2, "Error!\nNo map passed.\n", 22);
	else if (error_code == ERR_ARGC_MAX)
		write(2, "Error!\nToo many arguments.\n", 27);
	else if (error_code == ERR_MAP_VALIDITY)
		write(2, "Error!\nMap is not valid.\n", 25);
	else if (error_code == ERR_MAP_C)
		write(2, "Error!\nMap params are bad. Check colours.\n", 42);
	else if (error_code == ERR_MAP_OPEN)
		write(2, "Error!\nMap borders are open.\n", 29);
	else if (error_code == ERR_MAP_BAD_ARG)
		write(2, "Error!\nMap arg is bad.\n", 23);
	exit(EXIT_FAILURE);
}

int				ft_close(int exit_code, t_game *sv)
{
	if (exit_code < 0)
		ft_error_close(exit_code);
	if (exit_code == 53)
	{
		mlx_destroy_window(sv->mlx, sv->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
