/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 19:40:31 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/08 19:40:41 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

_Bool 		texture_paths_filled(t_conf *map)
{
	return (map->no_path && map->so_path && \
			map->we_path && map->ea_path && map->s_path);
}


static void			save_path(char **dst, const char *src)
{
	if (*dst)
		ft_error_close(ERR_MAP_T);
	else if (!(*dst = ft_strdup(src)))
		ft_error_close(ERR_MALLOC);
}

void			parse_textures(const char *str, t_conf *map)
{
	if (ft_strnstr(str, "NO ", 3) && !(ft_isspace(str[3])))
		save_path(&map->no_path, str + 3);
	else if (ft_strnstr(str, "SO ", 3) && !(ft_isspace(str[3])))
		save_path(&map->so_path, str + 3);
	else if (ft_strnstr(str, "WE ", 3) && !(ft_isspace(str[3])))
		save_path(&map->we_path, str + 3);
	else if (ft_strnstr(str, "EA ", 3) && !(ft_isspace(str[3])))
		save_path(&map->ea_path, str + 3);
	else if (str[0] == 'S' && str[1] == ' ' && !(ft_isspace(str[2])))
		save_path(&map->s_path, str + 2);
	else
		ft_error_close(ERR_MAP_T);
}

