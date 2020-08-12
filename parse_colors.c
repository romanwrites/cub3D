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

static _Bool 		count_commas(const char *str)
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

static void			check_rgb(char	**rgb)
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

void				parse_color(const char *str, t_conf *map)
{
	int				i;
	char			**rgb;
	static _Bool	f;
	static _Bool	c;
	int				j;

	i = 2;
	j = -1;
	if ((str[0] == 'C' && c) || (str[0] == 'F' && f) || \
		str[1] != ' ' || !(ft_isdigit(str[2])) || !(count_commas(str)))
		ft_error_close(ERR_MAP_C);
	while (ft_isdigit(str[i]) || str[i] == ',')
		i++;
	if (i > 13 || str[i] != '\0')
		ft_error_close(ERR_MAP_C);
	if (!(rgb = ft_split(str + 2, ',')))
		ft_error_close(ERR_MALLOC);
	check_rgb(rgb);
	if (str[0] == 'C')
	{
		while (j++ < 2)
			map->ceiling_color[j] = ft_atoi(rgb[j]);
		c = 1;
	}
	else if (str[0] == 'F')
	{
		while (j++ < 2)
			map->floor_color[j] = ft_atoi(rgb[j]);
		f = 1;
	}
	else
		ft_error_close(ERR_MAP_C);
}