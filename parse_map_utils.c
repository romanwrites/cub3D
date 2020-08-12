/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 19:35:44 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/08 19:36:39 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

_Bool				ft_all_isprint(const char *s)
{
	int i;

	i = 0;
	while (ft_isprint((int)s[i]))
		i++;
	if (s[i] != '\0')
		return (0);
	else
		return (1);
}

_Bool				ft_all_digits(const char *s)
{
	int	i;

	i = 0;
	while (ft_isdigit(s[i]))
		i++;
	if (s[i] != '\0')
		return (0);
	else
		return (1);
}

_Bool 		is_valid_map_bit(char c)
{
	return (c == '0' || c == '1' || c == '2' || c == ' ' || \
			c == 'N' || c == 'S' || c == 'W' || c == 'E');
}