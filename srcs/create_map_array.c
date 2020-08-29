/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:53:04 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/26 18:53:07 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		set_sprites_coordinates(t_game *sv)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (sv->map.map_array[i])
	{
		if (sv->map.map_array[i] == '2')
		{
			sv->sprites_on_map[j].x = i % sv->map.map_cols + 0.5;
			sv->sprites_on_map[j].y = i / sv->map.map_rows + 0.5;
			j++;
		}
		i++;
	}
}

void		create_map_array(t_game *sv)
{
	int		i;
	int		j;

	j = 0;
	ft_alloc_check(sv->map.map_array = ft_calloc(1, \
			sv->map.map_rows * sv->map.map_cols + 1));
	while (sv->lst)
	{
		i = 0;
		while (((char *)sv->lst->content)[i])
		{
			sv->map.map_array[j] = ((char *)sv->lst->content)[i];
			if (sv->map.map_array[j] == 'N' || sv->map.map_array[j] == 'S' || \
				sv->map.map_array[j] == 'W' || sv->map.map_array[j] == 'E')
				set_player_vectors(sv, j, i);
			if (sv->map.map_array[j] == '2')
				sv->sprites_count++;
			i++;
			j++;
		}
		sv->lst = sv->lst->next;
	}
	sv->map.map_array[j] = '\0';
	sv->sprites_on_map = malloc(sizeof(t_sprite) * sv->sprites_count);
	ft_alloc_check(sv->sprites_on_map);
}
