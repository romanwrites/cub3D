/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 16:30:39 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/31 16:30:54 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				perform_dda(t_game *sv)
{
	while (sv->map.hit == 0)
	{
		if (sv->map.side_dist_x < sv->map.side_dist_y)
		{
			sv->map.side_dist_x += sv->map.delta_dist_x;
			sv->map.map_x += sv->map.step_x;
			sv->map.side = 0;
		}
		else
		{
			sv->map.side_dist_y += sv->map.delta_dist_y;
			sv->map.map_y += sv->map.step_y;
			sv->map.side = 1;
		}
		if (sv->map.map_arr[sv->map.map_x + sv->map.map_y * sv->map.max_len] \
																	== '1')
			sv->map.hit = 1;
	}
}
