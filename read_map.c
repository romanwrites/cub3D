/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 17:32:13 by mkristie          #+#    #+#             */
/*   Updated: 2020/08/25 18:17:03 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			read_map(const int fd, t_game *sv)
{
	int				bytes;

	sv->lst = ft_my_lstnew(NULL, NULL);
	ft_alloc_check(sv->lst);
	sv->head = sv->lst;
	while ((bytes = get_next_line(fd, (char **)&sv->lst->content)) == 1)
	{
		ft_alloc_check(sv->lst->content);
		sv->lst->next = ft_my_lstnew(NULL, &sv->lst);
		ft_alloc_check(sv->lst->next);
		sv->lst->len = ft_strlen(sv->lst->content);
		sv->lst = sv->lst->next;
	}
	sv->lst->len = ft_strlen(sv->lst->content);
	if (bytes == -1)
		exit_with_err_msg("Can't read map");
	close(fd);
}
