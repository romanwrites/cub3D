/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 11:03:51 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/02 11:34:51 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>

unsigned int		create_trgb(unsigned int t, unsigned int r, \
								unsigned int g, unsigned int b);
unsigned int		get_t(unsigned int trgb);
unsigned int		get_r(unsigned int trgb);
unsigned int		get_g(unsigned int trgb);
unsigned int		get_b(unsigned int trgb);
unsigned int		add_shade(double distance, unsigned int color);
unsigned int		get_opposite(unsigned int color);

#endif