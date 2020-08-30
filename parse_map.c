/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:19:12 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/30 17:45:04 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t			find_max_len(t_game *sv)
{
	size_t		max;

	max = 0;
	while (sv->tmp->next != NULL)
	{
		if (max < sv->tmp->len)
			max = sv->tmp->len;
		sv->tmp = sv->tmp->next;
	}
	sv->map.max_len = max;
	return (max);
}


void			append_spaces(const char *src, t_game *sv, size_t len)
{
	char		*dst;
	size_t 		i;

	i = 0;
	if (!(dst = ft_calloc(1, len + 1)))
		ft_error_close(ERR_MALLOC);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = ' ';
		i++;
	}
	dst[i] = '\0';
	free(sv->tmp->content);
	sv->tmp->content = dst;
}


void			convert_spaces_to_ones(t_game *sv)
{
	int			i;

	i = 0;
	while (sv->tmp != NULL)
	{
		while (((char *)(sv->tmp->content))[i])
		{
			if (((char *)(sv->tmp->content))[i] == ' ')
			{
				((char *)(sv->tmp->content))[i] = '1';
			}
			i++;
		}
		i = 0;
		sv->tmp = sv->tmp->next;
	}
}

void			append_to_max_len(t_game *sv)
{
	sv->map.map_cols = find_max_len(sv);
	sv->tmp = sv->lst;
	while (sv->tmp->next != NULL)
	{
		if (sv->tmp->len < sv->map.map_cols)
			append_spaces(sv->tmp->content, sv, sv->map.map_cols);
		sv->tmp = sv->tmp->next;
	}
	if (sv->tmp->len < sv->map.map_cols)
		append_spaces(sv->tmp->content, sv, sv->map.map_cols);
}

void			parse_map(t_game *sv)
{
	sv->tmp = sv->lst;
	all_map_bits_are_valid(sv);
	check_horizontal_border(sv->tmp->content);
	sv->map.map_rows += 1;
	sv->tmp = sv->lst;
	check_horizontal_border(sv->tmp->content);
	sv->map.map_rows += 1;
	check_vertical_borders(sv);
	append_to_max_len(sv);
	sv->tmp = sv->lst->next;
	while (sv->tmp->next->next != NULL)
	{
		sv->map.map_rows += 1;
		check_sign(sv->tmp->content, sv->tmp->previous->content, \
					sv->tmp->next->content, sv);
		sv->tmp = sv->tmp->next;
	}
	sv->map.map_rows += 1;
	sv->tmp = sv->lst;
	convert_spaces_to_ones(sv);
}