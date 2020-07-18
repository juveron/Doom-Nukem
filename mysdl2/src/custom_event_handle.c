/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_event_handle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 15:40:30 by thboura           #+#    #+#             */
/*   Updated: 2020/05/31 15:42:53 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_handle.h"

bool	add_custom_action(t_event_handler *event_handler,
	t_custom_event *event)
{
	t_dlist			*node;

	node = ft_dlistnew(event, sizeof(t_custom_event));
	if (!ft_dlistaddend(event_handler->dlist_handler, node))
		return (false);
	return (true);
}

void	remove_custom_action(t_event_handler *event_handler,
	t_custom_event *event)
{
	t_dlist	*list;

	list = event_handler->dlist_handler->head;
	while (list)
	{
		if (ft_memcmp(list->content, event, sizeof(t_custom_event)) == 0)
		{
			ft_dlistdelone(event_handler->dlist_handler, list, NULL);
			return ;
		}
		list = list->next;
	}
}

bool	trigger_custom_event(t_event_handler *event_handler,
	void *param)
{
	t_dlist	*current;

	current = event_handler->dlist_handler->head;
	while (current)
	{
		if (!((t_custom_event *)current->content)->func(param,
				((t_custom_event *)current->content)->param))
			return (false);
		current = current->next;
	}
	return (true);
}
