/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_event.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 16:20:10 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/13 17:31:11 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	free_all_event(t_env *env)
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
	ft_dlistdel(&env->editor.event_handler.event_list, NULL);
}
