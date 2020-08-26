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

void		create_map_array(t_game *sv)
{
	int		i;
	int 	j;

	i = 0;
	j = 0;
	if (!(sv->map.map_array = ft_calloc(1, sv->map.map_rows * sv->map.map_cols + 1)))
		ft_error_close(ERR_MALLOC);
	while (sv->lst)
	{
		while (((char *)sv->lst->content)[i])
		{
			sv->map.map_array[j] = ((char *)sv->lst->content)[i];
			if (sv->map.map_array[j] == 'N' || sv->map.map_array[j] == 'S' || \
				sv->map.map_array[j] == 'W' || sv->map.map_array[j] == 'E')
			{
				set_player_vectors(sv, j, i);
			}
			i++;
			j++;
		}
		i = 0;
		sv->lst = sv->lst->next;
	}
	sv->map.map_array[j] = '\0';
}
