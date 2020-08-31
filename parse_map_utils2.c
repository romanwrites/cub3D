/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:23:05 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/30 17:47:06 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			check_map_params(t_game *sv)
{
	_Bool		map_started_flag;

	map_started_flag = 0;
	sv->lst = sv->head;
	while (sv->lst->next != NULL && !map_started_flag)
	{
		what_is_line_content(sv->lst->content, sv, &map_started_flag);
		if (!map_started_flag)
			sv->lst = sv->lst->next;
	}
}

void			check_horizontal_border(const char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == '1' || str[i] == ' '))
			ft_error_close(ERR_MAP_OPEN);
		i++;
	}
}

void			check_vertical_borders(t_game *sv)
{
	while (sv->tmp)
	{
		if (!(((char *)(sv->tmp->content))[0] == '1' || \
			((char *)(sv->tmp->content))[0] == ' ') || \
			!(((char *)(sv->tmp->content))[sv->tmp->len - 1] == '1' || \
			((char *)(sv->tmp->content))[sv->tmp->len - 1] == ' '))
			ft_error_close(ERR_MAP_OPEN);
		sv->tmp = sv->tmp->next;
	}
	sv->tmp = sv->lst;
}

void			check_sign(const char *str, const char *previous, \
							const char *next, t_game *sv)
{
	size_t		j;

	j = 1;
	while (j < sv->tmp->len - 1)
	{
		if (str[j] == 'N' || str[j] == 'S' || str[j] == 'E' || str[j] == 'W')
		{
			if (!(sv->map.player_direction))
				sv->map.player_direction = str[j];
			else
				ft_error_close(ERR_MAP_VALIDITY);
		}
		if (str[j] != '1' && str[j] != ' ' )
		{
			if (str[j - 1] == ' ' || (str[j + 1] == ' ' || str[j + 1] == '\0') || \
                previous[j] == ' ' || next[j] == ' ')
				ft_error_close(ERR_MAP_OPEN);
		}
		j++;
	}
}
