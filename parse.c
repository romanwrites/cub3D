/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:32:00 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/25 18:40:18 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			what_is_line_content(char *str, t_game *sv, \
									_Bool *map_started_flag)
{
	if (!(*str) && !(*map_started_flag))
		return ;
	else if (!(*str) && *map_started_flag)
		exit_with_err_msg("Map is not valid.");
	if (*str == ' ')
	{
		while (*str == ' ')
			str++;
	}
	if (*str == 'R')
		parse_resolution(sv, str, &sv->map);
	else if (*str == 'N' || *str == 'S' || *str == 'W' || *str == 'E')
		handle_textures(str, &sv->map);
	else if (*str == 'C' || *str == 'F')
		handle_color(str, &sv->map);
	else if (!(*map_started_flag) && (*str == '1' || *str == ' '))
	{
		*map_started_flag = 1;
		parse_map(sv);
	}
	else
		exit_with_err_msg("Map is not valid.");
}
