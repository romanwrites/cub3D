/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 18:24:38 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/01 18:24:46 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cub3d.h"

_Bool		is_valid_map_file(t_checklist *chk)
{
	if (!chk->no_txt || !chk->so_txt || !chk->ea_txt || !chk->we_txt || \
		!chk->sprite_txt || !chk->res_width || !chk->res_height || \
		!chk->floor_c || !chk->ceiling_c || !chk->m || !chk->player)
		return (0);
	if (chk->no_txt > 1 || chk->so_txt > 1 || chk->ea_txt > 1 || \
		chk->we_txt > 1 || chk->sprite_txt > 1 || chk->res_width > 1 || \
		chk->res_height > 1 || chk->floor_c > 1 || chk->ceiling_c > 1 || \
		chk->m > 1 || chk->player > 1)
		return (0);
	return (1);
}

void		free_lst_content(void *content)
{
	free(content);
	content = NULL;
}

void		check_res(t_game *sv)
{
	if (sv->map.res_w < 64)
		sv->map.res_w = 64;
	if (sv->map.res_h < 64)
		sv->map.res_h = 64;
	while (sv->map.res_w % 64 != 0)
		sv->map.res_w += 1;
	while (sv->map.res_h % 64 != 0)
		sv->map.res_h += 1;
}

_Bool		count_commas(const char *str)
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
