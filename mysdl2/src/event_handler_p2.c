/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler_p2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 14:56:25 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/01 14:56:27 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_handle.h"
#include "context.h"

bool	trigger_gui_custom_event(t_event_handler *event_handler, void *param)
{
	t_event_vector	v;

	v.param = param;
	v.event_handler = event_handler;
	return (vector_push(&get_context()->gui_trigger, &v));
}

bool	trigger_gui_default_event(t_event_handler *event_handler)
{
	t_event_vector	v;

	v.event_handler = event_handler;
	return (vector_push(&get_context()->gui_trigger, &v));
}

bool	trigger_gui_event(void)
{
	t_context		*context;
	t_event_vector	*v;
	size_t			i;

	context = get_context();
	v = context->gui_trigger.items;
	i = 0;
	while (i < context->gui_trigger.total)
	{
		if (v[i].event_handler->event_type == DEFAULT_EVENT_TYPE)
		{
			if (!trigger_default_event(v[i].event_handler))
				return (false);
		}
		else if (v[i].event_handler->event_type == CUSTOM_EVENT_TYPE)
			if (!trigger_custom_event(v[i].event_handler, v[i].param))
				return (false);
		++i;
	}
	vector_free(&context->gui_trigger);
	if (!vector_init(&context->gui_trigger, sizeof(t_event_vector)))
		return (false);
	return (true);
}
