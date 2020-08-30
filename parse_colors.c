/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 19:43:50 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/08 19:43:56 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static _Bool		count_commas(const char *str)
{
	int				commas;
	int				i;

	commas = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			commas++;
		i++;
	}
	return (commas == 2);
}

static void			check_rgb(char **rgb)
{
	int				i;

	i = 0;
	while (rgb[i])
	{
		if (ft_strlen(rgb[i]) < 1 || ft_strlen(rgb[i]) > 3)
			ft_error_close(ERR_MAP_C);
		i++;
	}
	if (i != 3)
		ft_error_close(ERR_MAP_C);
}

void				set_color(const char *str, t_conf *map, char **rgb)
{
	int				j;

	j = -1;
	if (str[0] == 'C')
	{
		while (j++ < 2)
			map->ceiling_rgb[j] = ft_atoi(rgb[j]);
		map->c_color_parse = 1;
		map->ceiling_color = create_trgb(0, map->ceiling_rgb[0], \
							map->ceiling_rgb[1], map->ceiling_rgb[2]);
	}
	else if (str[0] == 'F')
	{
		while (j++ < 2)
			map->floor_rgb[j] = ft_atoi(rgb[j]);
		map->f_color_parse = 1;
		map->floor_color = create_trgb(0, map->floor_rgb[0], \
							map->floor_rgb[1], map->floor_rgb[2]);
	}
	else
		ft_error_close(ERR_MAP_C);
}

void				parse_color(const char *str, t_conf *map)
{
	int				i;
	char			**rgb;

	i = 2;
	if ((str[0] == 'C' && map->c_color_parse) \
		|| (str[0] == 'F' && map->f_color_parse) || \
		!(ft_isdigit(str[1])) || !(count_commas(str)))
		ft_error_close(ERR_MAP_C);
	while (ft_isdigit(str[i]) || str[i] == ',')
		i++;
	if (i > 13 || str[i] != '\0')
		ft_error_close(ERR_MAP_C);
	if (!(rgb = ft_split(str + 1, ',')))
		ft_error_close(ERR_MALLOC);
	check_rgb(rgb);
	set_color(str, map, rgb);
	ft_free2d(rgb);
}

void				handle_color(const char *str, t_conf *map)
{
	char			*tmp;

	if (!(ft_all_isprint(str)))
		ft_error_close(ERR_MAP_C);
	if (!(tmp = ft_replace(str, " ", "")))
		ft_error_close(ERR_MALLOC);
	parse_color(tmp, map);
	free(tmp);
}