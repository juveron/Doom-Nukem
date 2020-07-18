/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_event_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 16:01:10 by thboura           #+#    #+#             */
/*   Updated: 2020/01/25 14:17:10 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	init_event_handler(t_recorded_event_handler *event_handler)
{
	if (!(event_handler->event_list = ft_dlist_create()))
		return (false);
	event_handler->current_event = NULL;
	return (true);
}

void	free_event_handler(t_recorded_event_handler *event_handler)
{
	ft_dlistdel(&event_handler->event_list, NULL);
	event_handler->current_event = NULL;
}
