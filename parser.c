/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 22:52:16 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/05 22:52:20 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef	struct		s_map
{
	t_lst			*head;
}					t_map;

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

_Bool 		is_valid_map_bit(char c)
{
	return (c == '0' || c == '1' || c == '2' || c == ' ' || \
			c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

//int				append_line(char *str, t_list *map, t_game *sv)
//{
//	char		*line;
//
//	line = str;
//	while (*str)
//	{
//		if (*str == 'N' || *str == 'S' || *str == 'E' || *str == 'W')
//		{
//			h->player++;
//			h->orient = *str;
//		}
//		if (*str == '2')
//			h->s_cnt++;
//		if (is_valid_map_bit(*str))
//			str++;
//		else
//			return (1);
//	}
//	if (*str != '\0')
//		return (1);
//	ft_lstadd_back(map, ft_lstnew(ft_strdup(line)));
//	return (0);
//}


void	ft_put_map_line(char *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}


void			read_map(const int fd, t_list **map, t_game *sv)
{
	printf("fd: %d\n", fd); //////debug
	char			*line;
	int				bytes_read;
	t_list			*elem;

	elem = ft_lstnew(NULL);
	*map = elem;
	while ((bytes_read = get_next_line(fd, (char **)&elem->content)) == 1)
	{
		if (!(elem->content) || !(elem->next = ft_lstnew(NULL)))
			ft_error_close(ERR_MALLOC);
		elem->len = ft_strlen(elem->content); //считаем длину каждой линии
		elem = elem->next;
	}
	elem->len = ft_strlen(elem->content);
	if (bytes_read == -1)
		ft_error_close(ERR_READ_MAP);
	close(fd);
//	ft_lstiter(map, (void *)ft_put_map_line);  //дебаг печать
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

