/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_lstclear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 16:13:15 by mkristie          #+#    #+#             */
/*   Updated: 2020/09/01 16:18:19 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Deletes and frees the given element and every
** successor of that element, using the function ’del’ and free(3).
** Finally, the pointer to the list must be set to NULL.
*/

void				ft_my_lstclear(t_d_list **lst, void (*del)(void *))
{
	t_d_list	*tmp;
	t_d_list	*start;

	if (!lst || !del)
		return ;
	start = *lst;
	while (start)
	{
		tmp = start->next;
		del(start->content);
		free(start);
		start = tmp;
	}
	*lst = NULL;
}
