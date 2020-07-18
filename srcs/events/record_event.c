/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:55:35 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 16:42:04 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	verify_handler(t_recorded_event_handler *event_handler, t_env *env)
{
	t_dlist		*tmp;

	if (event_handler->current_event != NULL
		&& event_handler->current_event->next != NULL)
	{
		tmp = event_handler->current_event->next;
		while (tmp != NULL)
		{
			event_handler->current_event = tmp->next;
			((t_recorded_event_func *)((t_recorded_event *)tmp->content)->
				param)->delete((t_recorded_event_func *)(
				(t_recorded_event *)tmp->content)->param);
			ft_dlistdelone(event_handler->event_list, tmp, NULL);
			tmp = event_handler->current_event;
		}
	}
	else if (!event_handler->current_event
		&& event_handler->event_list->size > 0)
	{
		free_all_event(env);
		if (!init_event_handler(event_handler))
			return (false);
	}
	return (true);
}

bool		record_event(t_env *env, t_recorded_event_type event_type,
	void *param)
{
	t_recorded_event			tmp_event;
	t_dlist						*tmp;
	t_recorded_event_handler	*event_handler;

	event_handler = &env->editor.event_handler;
	tmp_event.param = param;
	tmp_event.type = event_type;
	if (!verify_handler(event_handler, env))
		return (false);
	if (event_handler->event_list->size == 50)
	{
		tmp = event_handler->event_list->head;
		event_handler->event_list->head = tmp->next;
		((t_recorded_event_func *)((t_recorded_event *)tmp->content)->param)->
			delete(((t_recorded_event *)tmp->content)->param);
		ft_dlistdelone(event_handler->event_list, tmp, NULL);
	}
	if (!ft_dlistaddend(event_handler->event_list, ft_dlistnew(&tmp_event,
		sizeof(t_recorded_event))))
		return (false);
	event_handler->current_event = event_handler->event_list->tail;
	display_events(env, 1);
	return (true);
}

bool		undo_event(t_recorded_event_handler *event_handler, t_env *env)
{
	bool				ret;
	t_recorded_event	*tmp_event;

	if (!event_handler->current_event)
		return (true);
	tmp_event = event_handler->current_event->content;
	ret = ((t_recorded_event_func *)tmp_event->param)->undo(env,
		tmp_event->param);
	event_handler->current_event = event_handler->current_event->prev;
	return (ret);
}

bool		redo_event(t_recorded_event_handler *event_handler, t_env *env)
{
	t_recorded_event	*tmp_event;

	if (!event_handler->event_list->size || !event_handler->event_list->tail
		|| (event_handler->current_event
			&& !event_handler->current_event->next))
		return (true);
	if (!event_handler->current_event)
	{
		tmp_event = event_handler->event_list->head->content;
		event_handler->current_event = event_handler->event_list->head;
	}
	else
	{
		tmp_event = event_handler->current_event->next->content;
		event_handler->current_event = event_handler->current_event->next;
	}
	return (((t_recorded_event_func *)tmp_event->param)->redo(env,
		tmp_event->param));
}
