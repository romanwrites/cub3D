/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 20:06:32 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/08 20:06:37 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		handle_resolution(const char *str, t_conf *map)
{
	char		**temp;

	temp = NULL;
	if (!(temp = ft_split(str, ' ')))
		ft_error_close(ERR_MALLOC);
	if (ft_two_d_counter(&temp) != 3 || \
			!(ft_all_digits(temp[1])) || !(ft_all_digits(temp[2])))
		ft_error_close(ERR_MAP_R);
	if (map->res_w || map->res_h)
		ft_error_close(ERR_MAP_R);
	map->res_w = ft_atoi(temp[1]);
	map->res_h = ft_atoi(temp[2]);
}

static void		handle_textures(const char *str, t_conf *map)
{
	if (texture_paths_filled(map) || !(ft_all_isprint(str)))
		ft_error_close(ERR_MAP_T);
	else
		parse_textures(str, map);
}

static void		handle_color(const char *str, t_conf *map)
{
	if (!(ft_all_isprint(str)))
		ft_error_close(ERR_MAP_C);
	parse_color(str, map);
}

void			check_sign(const char *str, const char *previous, const char *next, t_game *sv)
{
	int		j;

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
			{
//				printf("filename: \n");
				ft_error_close(ERR_MAP_OPEN);
			}

		}
		j++;
	}
}

int			find_max_len(t_game *sv)
{
	int		max;

	max = 0;
	while (sv->tmp->next != NULL)
	{
		if (max < sv->tmp->len)
			max = sv->tmp->len;
		sv->tmp = sv->tmp->next;
	}
	sv->map.max_len = max;
	printf("max_len = %d\n", max); //debug print
	return (max);
}

void			all_map_bits_are_valid(t_game *sv)
{
	int 	i;

	i = 0;
	while (sv->tmp->next != NULL)
	{
		while (is_valid_map_bit(((char *)(sv->tmp->content))[i]))
		{
			i++;
		}
		if ((((char *)(sv->tmp->content))[i]) != '\0')
			ft_error_close(ERR_MAP_VALIDITY);
		i = 0;
		sv->tmp = sv->tmp->next;
	}
	while (is_valid_map_bit(((char *)(sv->tmp->content))[i]))
	{
		i++;
	}
	if ((((char *)(sv->tmp->content))[i]) != '\0')
		ft_error_close(ERR_MAP_VALIDITY);
}

void			append_spaces(const char *src, t_game *sv, size_t len)
{
	char		*dst;
	int 		i;

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
//	printf("len content: %zu, len dst: %zu\n", ft_strlen(sv->tmp->content), ft_strlen(dst));
	free(sv->tmp->content);
	sv->tmp->content = dst;
}

void			append_to_max_len(t_game *sv)
{
//	size_t		max_len;

//	sv->tmp = sv->lst;
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

void			check_horizontal_border(const char *str)
{
	int		i;

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
		if (!(((char *)(sv->tmp->content))[0] == '1' || ((char *)(sv->tmp->content))[0] == ' ') || \
			!(((char *)(sv->tmp->content))[sv->tmp->len - 1] == '1' || ((char *)(sv->tmp->content))[sv->tmp->len - 1] == ' '))
			ft_error_close(ERR_MAP_OPEN);
		sv->tmp = sv->tmp->next;
	}
	sv->tmp = sv->lst;
}

void			convert_spaces_to_ones(t_game *sv)
{
	int	i;

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
//		printf("KEK: %s\n", sv->tmp->previous->content);
		sv->tmp = sv->tmp->next;
	}
}

void			parse_map(t_game *sv)
{
	int	i;

	i = 0;
	sv->tmp = sv->lst;
	all_map_bits_are_valid(sv);
	check_horizontal_border(sv->tmp->content);
	sv->map.map_rows += 1; //count lines: top line
//	printf("bottom: %s\n", sv->tmp->content);
	sv->tmp = sv->lst;
	check_horizontal_border(sv->tmp->content);
	sv->map.map_rows += 1; //count lines: bottom line
//	printf("top: %s\n", sv->tmp->content);
	check_vertical_borders(sv);
	append_to_max_len(sv);
	sv->tmp = sv->lst->next;
	while (sv->tmp->next->next != NULL)
	{
		sv->map.map_rows += 1; //count lines
		check_sign(sv->tmp->content, sv->tmp->previous->content, sv->tmp->next->content, sv);
//		printf("KEK: %s\n", sv->tmp->previous->content);
		sv->tmp = sv->tmp->next;
	}
	sv->map.map_rows += 1;
	sv->tmp = sv->lst;
	convert_spaces_to_ones(sv);
//	printf("KEK: %s\n", sv->tmp->previous->content);
	//after null next content hz
//	printf("KEK: %s\n", sv->lst->content);
}

void			what_is_line_content(const char *str, t_game *sv, \
									_Bool *map_started_flag)
{
	if (!(*str) && !(*map_started_flag))
		return ;
	else if (!(*str) && *map_started_flag)
		ft_error_close(ERR_MAP_VALIDITY);
//	if (ft_isspace(*str) && !(*map_started_flag))
//	{
//		printf("filename: \n");
//		ft_error_close(ERR_MAP_BAD_ARG);
//	}
	else if (*str == 'R')
		handle_resolution(str, &sv->map);
	else if (*str == 'N' || *str == 'S' || *str == 'W' || *str == 'E')
		handle_textures(str, &sv->map);
	else if (*str == 'C' || *str == 'F')
		handle_color(str, &sv->map);
	else if (!(*map_started_flag) && (*str == '1' || *str == ' '))
	{
		*map_started_flag = 1;
		parse_map(sv);
	}
	else
	{
		ft_error_close(ERR_MAP_VALIDITY);
	}

//	printf("%s\n%d %d\n", str, map->res_w, map->res_h);
}