/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlistaddend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 12:21:03 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/04 13:18:41 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlistaddend(t_dlist_handler *dlist_handler, t_dlist *node)
{
	if (!node)
		return (NULL);
	if (dlist_handler->tail == NULL)
	{
		dlist_handler->tail = node;
		dlist_handler->head = node;
	}
	else
	{
		dlist_handler->tail->next = node;
		node->prev = dlist_handler->tail;
		dlist_handler->tail = node;
	}
	dlist_handler->size++;
	return (node);
}
