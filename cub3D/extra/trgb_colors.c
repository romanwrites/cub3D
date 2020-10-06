/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trgb_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 23:53:43 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/01 18:43:31 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** bitshifting
*/

unsigned int		create_trgb(unsigned int t, unsigned int r, \
								unsigned int g, unsigned int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/*
** retrieve integer values from a encoded TRGB integer
*/

unsigned int		get_t(unsigned int trgb)
{
	return (trgb & (0xFF << 24));
}

unsigned int		get_r(unsigned int trgb)
{
	return (trgb & (0xFF << 16));
}

unsigned int		get_g(unsigned int trgb)
{
	return (trgb & (0xFF << 8));
}

unsigned int		get_b(unsigned int trgb)
{
	return (trgb & 0xFF);
}
