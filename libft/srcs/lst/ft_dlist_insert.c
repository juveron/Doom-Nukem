/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 11:02:24 by kguibout          #+#    #+#             */
/*   Updated: 2020/02/17 13:22:59 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_lst.h"

t_dlist	*ft_dlist_insert(t_dlist_handler *handler, t_dlist *node, t_dlist *new)
{
	if (!new)
		return (NULL);
	new->next = node;
	new->prev = node->prev;
	new->prev->next = new;
	node->prev = new;
	if (handler->head == node)
		handler->head = new;
	handler->size++;
	return (new);
}
