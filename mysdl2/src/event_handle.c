/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 12:04:12 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/31 15:42:33 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_handle.h"

t_event_handler	*create_event_handler(t_event_type event_type)
{
	t_event_handler *event_handler;

	if (!(event_handler = malloc(sizeof(t_event_handler))))
		return (NULL);
	event_handler->event_type = event_type;
	if (!(event_handler->dlist_handler = ft_dlist_create()))
	{
		free(event_handler);
		return (NULL);
	}
	return (event_handler);
}

void			destroy_event_handler(t_event_handler *event_handler)
{
	if (event_handler == NULL)
		return ;
	ft_dlistdel(&event_handler->dlist_handler, NULL);
	free(event_handler);
}

bool			add_default_action(t_event_handler *event_handler,
	t_default_event *event)
{
	t_dlist			*node;

	node = ft_dlistnew(event, sizeof(t_default_event));
	if (!ft_dlistaddend(event_handler->dlist_handler, node))
		return (false);
	return (true);
}

void			remove_default_action(t_event_handler *event_handler,
	t_default_event *event)
{
	t_dlist	*list;

	list = event_handler->dlist_handler->head;
	while (list)
	{
		if (ft_memcmp(list->content, event, sizeof(t_default_event)) == 0)
		{
			ft_dlistdelone(event_handler->dlist_handler, list, NULL);
			return ;
		}
		list = list->next;
	}
}

bool			trigger_default_event(t_event_handler *event_handler)
{
	t_dlist	*current;

	current = event_handler->dlist_handler->head;
	while (current)
	{
		if (!((t_default_event *)current->content)->func((
			(t_default_event *)current->content)->param))
			return (false);
		current = current->next;
	}
	return (true);
}
