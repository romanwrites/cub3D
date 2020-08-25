/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 20:06:32 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/08 20:06:37 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	res_utils(char *str, t_conf *map)
{
	char	*replaced;
	char	**temp;

	if (!(replaced = ft_replace(str, " ", "")))
		ft_error_close(ERR_MALLOC);
	if (!(temp = ft_split(replaced, ',')))
		ft_error_close(ERR_MALLOC);
	if (ft_two_d_counter(&temp) != 2 || \
			!(ft_all_digits(temp[0])) || !(ft_all_digits(temp[1])))
		ft_error_close(ERR_MAP_R);
	if (map->res_w || map->res_h)
		ft_error_close(ERR_MAP_R);
	map->res_w = ft_atoi(temp[0]);
	map->res_h = ft_atoi(temp[1]);
	if (map->res_h > 3500 || map->res_w > 3500 || \
		map->res_h < 1 || map->res_w < 1)
		ft_error_close(ERR_MAP_R);
	free(replaced);
	ft_free2d(temp);
}

void		parse_resolution(char *str, t_conf *map)
{
	int		i;

	i = 0;
	if (str[0] == 'R' && str[1] == ' ')
		str += 2;
	while (str[i] == ' ')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == ' ')
		str[i] = ',';
	else
		ft_error_close(ERR_MAP_R);
	res_utils(str, map);
}
