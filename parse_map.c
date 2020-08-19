/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 17:32:13 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/08 19:37:32 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void			check_map_params(t_game *sv)
{
	_Bool			map_started_flag;

	map_started_flag = 0;
	sv->lst = sv->head;
	while (sv->lst->next != NULL && !map_started_flag)
	{
		what_is_line_content(sv->lst->content, sv, &map_started_flag);
		if (!map_started_flag)
			sv->lst = sv->lst->next;
	}
}

void			read_map(const int fd, t_game *sv)
{
	char			*line;
	int				bytes_read;

	sv->lst = ft_my_lstnew(NULL, NULL);
	sv->head = sv->lst;
	while ((bytes_read = get_next_line(fd, (char **)&sv->lst->content)) == 1)
	{
		if (!(sv->lst->content) || !(sv->lst->next = ft_my_lstnew(NULL, &sv->lst)))
			ft_error_close(ERR_MALLOC);
//		if (sv->lst->previous)
//			printf("%s\n", sv->lst->previous->content);
		sv->lst->len = ft_strlen(sv->lst->content); //считаем длину каждой линии
//		printf("linelen: %zu\n", sv->lst->len);
		sv->lst = sv->lst->next;
	}
	sv->lst->len = ft_strlen(sv->lst->content);
	if (bytes_read == -1)
		ft_error_close(ERR_READ_MAP);
	close(fd);
	check_map_params(sv);
//	ft_lstiter(map, (void *)ft_put_map_line);  //дебаг печать
}
