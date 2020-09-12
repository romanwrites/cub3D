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

static _Bool	texture_paths_filled(t_conf *map)
{
	return (map->no_path && map->so_path && \
			map->we_path && map->ea_path && map->s_path);
}

static void		save_path(char **dst, const char *src)
{
	while (*src == ' ')
		src++;
	if (*dst)
		exit_with_err_msg("Map params are bad. Check texture paths.");
	*dst = ft_strdup(src);
	ft_alloc_check(*dst);
}

static void		parse_textures(t_game *sv, const char *str, t_conf *map)
{
	if (ft_strnstr(str, "NO", 2))
	{
		save_path(&map->no_path, str + 2);
		sv->checklist.no_txt += 1;
	}
	else if (ft_strnstr(str, "SO", 2))
	{
		save_path(&map->so_path, str + 2);
		sv->checklist.so_txt += 1;
	}
	else if (ft_strnstr(str, "WE", 2))
	{
		save_path(&map->we_path, str + 2);
		sv->checklist.we_txt += 1;
	}
	else if (ft_strnstr(str, "EA", 2))
	{
		save_path(&map->ea_path, str + 2);
		sv->checklist.ea_txt += 1;
	}
	else if (str[0] == 'S')
	{
		save_path(&map->s_path, str + 1);
		sv->checklist.sprite_txt += 1;
	}
	else
		exit_with_err_msg("Map params are bad. Check texture parameters.");
}

void			handle_textures(t_game *sv, const char *str, t_conf *map)
{
//	char		*tmp;

	if (texture_paths_filled(map) || !(ft_all_isprint(str)))
		exit_with_err_msg("Map params are bad. Check texture parameters.");
//	tmp = ft_replace(str, " ", "");
//	ft_alloc_check(tmp);
//	while (*str == ' ')
//		str++;
	parse_textures(sv, str, map);
//	free(tmp);
}
