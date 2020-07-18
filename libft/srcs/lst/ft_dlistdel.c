/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlistdel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 22:13:30 by kguibout          #+#    #+#             */
/*   Updated: 2020/02/17 15:30:05 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlistdel(t_dlist_handler **dlist_handler, void (*del)(void *))
{
	t_dlist	*nxt;
	t_dlist	*cur;

	cur = (*dlist_handler)->head;
	while (cur != NULL)
	{
		nxt = cur->next;
		if (del)
			del(cur->content);
		free(cur->content);
		free(cur);
		cur = nxt;
	}
	free(*dlist_handler);
	*dlist_handler = NULL;
}
