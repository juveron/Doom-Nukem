/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pickup_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:49:48 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 15:33:26 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	undo_pickup_object(t_env *env, void *param)
{
	t_rec_add_pickup_event	*tmp;

	tmp = (t_rec_add_pickup_event *)param;
	return ((delete_pickup_object(env, &tmp->param.pos, false) == 0)
		&& change_selection_mode(env, EDITOR_OBJECT));
}

static bool	redo_pickup_object(t_env *env, void *param)
{
	t_rec_add_pickup_event	*tmp;
	t_sector				*tmp_sector;

	tmp = (t_rec_add_pickup_event *)param;
	if (!(tmp_sector = *(t_sector **)map_get(env->current_map->sectors,
		tmp->param.sector_id)))
		return (false);
	return ((add_pickup_object_p2(env, &tmp->param.pos, tmp_sector, false) == 0)
		&& change_selection_mode(env, EDITOR_OBJECT));
}

static bool	delete_event(void *param)
{
	free(param);
	return (false);
}

bool		add_pickup_object_event(t_env *env, t_pickup_object *pickup_object)
{
	t_rec_add_pickup_event	*tmp;

	if (!(tmp = (t_rec_add_pickup_event *)malloc(sizeof(
		t_rec_add_pickup_event))))
		return (false);
	tmp->param = *pickup_object;
	tmp->func.redo = &redo_pickup_object;
	tmp->func.undo = &undo_pickup_object;
	tmp->func.delete = &delete_event;
	if (!record_event(env, REC_EVENT_ADD_PICKUP, (void *)tmp))
		return (delete_event(tmp));
	return (true);
}
