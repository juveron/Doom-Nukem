/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_index.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 07:43:21 by kguibout          #+#    #+#             */
/*   Updated: 2020/03/04 07:48:12 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlist_get_by_index(t_dlist_handler *list, size_t index)
{
	size_t		i;
	t_dlist		*tmp_dlist;

	if (index >= list->size || list->head == NULL)
		return (NULL);
	tmp_dlist = list->head;
	i = 0;
	while (i < index)
	{
		if (tmp_dlist == list->tail)
			return (NULL);
		tmp_dlist = tmp_dlist->next;
		i++;
	}
	return (tmp_dlist);
}

size_t	ft_dlist_get_index(t_dlist_handler *list, t_dlist *dlist)
{
	size_t		i;
	t_dlist		*tmp_dlist;

	if (dlist == NULL || list->head == NULL)
		return ((size_t)-1);
	tmp_dlist = list->head;
	i = 0;
	while (tmp_dlist != NULL)
	{
		if (tmp_dlist == dlist)
			return (i);
		tmp_dlist = tmp_dlist->next;
		i++;
	}
	return ((size_t)-1);
}
