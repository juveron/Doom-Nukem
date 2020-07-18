/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 19:55:45 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 19:55:46 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	clear_event(t_env *env)
{
	t_dlist	*list;
	t_dlist	*tmp;

	list = env->editor.event_handler.event_list->head;
	while (list != NULL)
	{
		tmp = list->next;
		((t_recorded_event_func *)((t_recorded_event *)list->content)->
				param)->delete((t_recorded_event_func *)(
				(t_recorded_event *)list->content)->param);
		ft_dlistdelone(env->editor.event_handler.event_list, list, NULL);
		list = tmp;
	}
	env->editor.event_handler.current_event = NULL;
}
