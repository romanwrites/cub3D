/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 22:52:16 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/25 18:32:56 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static _Bool 		check_str(const char *str, const char *s, const int num)
{
	size_t	len;

	len = 0;
	if (*str && (len = ft_strlen(str)))
	{
		if (len < 5)
			return (0);
		if (!(ft_strncmp(&str[len - num], s, num)))
			return (1);
	}
	return (0);
}

_Bool		parse_args(int ac, char *filename, char *save)
{
	_Bool 	s_flag;

	s_flag = 0;
	if (!(check_str(filename, ".cub", 4)))
		ft_error_close(ERR_FILENAME);
	if (ac == 2 && !save)
		s_flag = 1;
	else if (ac == 3 && save != NULL)
		s_flag = check_str(save, "--save", 6);
	if (!s_flag)
		ft_error_close(ERR_ARG_SAVE);
	return (1);
}

