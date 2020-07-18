/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlistaddfront.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 12:21:03 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/04 13:47:36 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlistaddfront(t_dlist_handler *dlist_handler, t_dlist *node)
{
	if (!node)
		return (NULL);
	if (dlist_handler->head == NULL)
	{
		dlist_handler->head = node;
		dlist_handler->tail = node;
	}
	else
	{
		dlist_handler->head->prev = node;
		node->next = dlist_handler->head;
		dlist_handler->head = node;
	}
	dlist_handler->size++;
	return (node);
}
