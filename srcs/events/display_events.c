/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 11:05:41 by thboura           #+#    #+#             */
/*   Updated: 2020/07/02 17:13:50 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static char	*get_event_type_p2(t_recorded_event_type type)
{
	if (type == REC_EVENT_ADD_PICKUP)
		return ("ADD_PICKUP_OBJECT");
	else if (type == REC_EVENT_DEL_PICKUP)
		return ("DELETE_PICKUP_OBJECT");
	else
		return (NULL);
}

char		*get_event_type(t_recorded_event_type type)
{
	if (type == REC_EVENT_ADD_POINT)
		return ("ADD_POINT");
	else if (type == REC_EVENT_INSERT_POINT)
		return ("INSERT_POINT");
	else if (type == REC_EVENT_DEL_POINT)
		return ("DELETE_POINT");
	else if (type == REC_EVENT_ADD_SECTOR)
		return ("ADD_SECTOR");
	else if (type == REC_EVENT_DEL_SECTOR)
		return ("DELETE_SECTOR");
	else if (type == REC_EVENT_MOVE_POINT)
		return ("MOVE_POINT");
	else if (type == REC_EVENT_ADD_START_LEVEL)
		return ("ADD_START_LEVEL");
	else if (type == REC_EVENT_ADD_END_LEVEL)
		return ("ADD_END_LEVEL");
	else if (type == REC_EVENT_MOVE_LEVEL_POINT)
		return ("MOVE_LEVEL_POINT");
	else if (type == REC_EVENT_DEL_LEVEL_POINT)
		return ("DELETE_LEVEL_POINT");
	else
		return (get_event_type_p2(type));
}

void		display_events(t_env *env, int new_elems)
{
	t_recorded_event_handler	*event_handler;

	event_handler = &env->editor.event_handler;
	if (!env->editor.history.available)
		return ;
	if (env->editor.history.event_selection->selected_index < event_handler->
		event_list->size && new_elems == 1)
	{
		env->editor.history.event_selection->selected_index++;
		if (env->editor.history.event_selection->selected_index > env->editor.
			history.event_selection->end)
		{
			env->editor.history.event_selection->end = env->editor.history.
				event_selection->selected_index;
			env->editor.history.event_selection->start = env->editor.history.
				event_selection->end - env->editor.history.event_selection->
				size;
		}
	}
	if (env->editor.history.event_selection->selected_index > 0
		&& new_elems == -1)
		env->editor.history.event_selection->selected_index--;
	env->editor.history.event_selection->component.need_redraw = true;
}
