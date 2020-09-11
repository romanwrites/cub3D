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