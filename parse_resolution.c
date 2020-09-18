/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 20:06:32 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/01 20:35:38 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	res_utils2(t_game *sv, t_conf *map)
{
	if (map->res_h > sv->get_res_h)
		map->res_h = sv->get_res_h;
	if (map->res_w > sv->get_res_w)
		map->res_w = sv->get_res_w;
	if (map->res_h < 1 || map->res_w < 1)
		exit_with_err_msg("Resolution is less than 1.");
}

static void	res_utils(t_game *sv, char *str, t_conf *map)
{
	char	*replaced;
	char	**temp;

	replaced = ft_replace(str, " ", "");
	ft_alloc_check(replaced);
	temp = ft_split(replaced, ',');
	ft_alloc_check(temp);
	if (ft_two_d_counter(&temp) != 2 || \
			!(ft_all_digits(temp[0])) || !(ft_all_digits(temp[1])))
		exit_with_err_msg("Map params are bad. Check R.");
	if (map->res_w || map->res_h)
		exit_with_err_msg("Resolution param passed twice.");
	if (ft_strlen(temp[0]) < 5)
		map->res_w = ft_atoi(temp[0]);
	else
		map->res_w = sv->get_res_w;
	if (ft_strlen(temp[1]) < 5)
		map->res_h = ft_atoi(temp[1]);
	else
		map->res_h = sv->get_res_h;
	res_utils2(sv, map);
	free(replaced);
	ft_free2d(temp);
	replaced = NULL;
	temp = NULL;
}

void		parse_resolution(t_game *sv, char *str, t_conf *map)
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
		exit_with_err_msg("Map params are bad. Check R.");
	mlx_get_screen_size(sv->mlx, &sv->get_res_w, &sv->get_res_h);
	res_utils(sv, str, map);
	sv->checklist.res_height += 1;
	sv->checklist.res_width += 1;
}
