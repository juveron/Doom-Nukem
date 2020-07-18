/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cancel_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 17:59:16 by thboura           #+#    #+#             */
/*   Updated: 2020/06/11 11:02:20 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	delete_next_events(t_recorded_event_handler *event_handler)
{
	t_dlist				*tmp;
	t_dlist				*store_current;

	store_current = event_handler->current_event;
	tmp = store_current->next;
	while (tmp != NULL)
	{
		event_handler->current_event = tmp->next;
		((t_recorded_event_func *)((t_recorded_event *)tmp->content)->
			param)->delete((t_recorded_event_func *)(
			(t_recorded_event *)tmp->content)->param);
		ft_dlistdelone(event_handler->event_list, tmp, NULL);
		tmp = event_handler->current_event;
	}
	event_handler->current_event = store_current;
}

static void	destroy_current_event(t_env *env, t_recorded_event **current_type,
	t_recorded_event_handler *event_handler)
{
	t_dlist		*tmp;

	tmp = event_handler->current_event->prev;
	((t_recorded_event_func *)((t_recorded_event *)event_handler->
		current_event->content)->param)->delete((t_recorded_event_func *)(
		(t_recorded_event *)event_handler->current_event->content)->param);
	ft_dlistdelone(event_handler->event_list,
		event_handler->current_event, NULL);
	event_handler->current_event = tmp;
	if (event_handler->current_event != NULL)
		*current_type = (t_recorded_event *)event_handler->
			current_event->content;
	if (env->editor.history.available)
		env->editor.history.event_selection->selected_index--;
}

void		cancel_sector_record(t_env *env)
{
	t_recorded_event			*current_type;
	t_recorded_event_handler	*event_handler;

	event_handler = &env->editor.event_handler;
	if (event_handler->current_event == NULL)
		return ;
	if (event_handler->current_event->next != NULL)
		delete_next_events(event_handler);
	current_type = (t_recorded_event *)event_handler->current_event->content;
	while (event_handler->current_event != NULL
		&& current_type->type == REC_EVENT_ADD_POINT)
		destroy_current_event(env, &current_type, event_handler);
	display_events(env, 0);
}
