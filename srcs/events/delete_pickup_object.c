/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_pickup_object.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:37:39 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 15:33:45 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	insert_pickup_object(t_env *env, t_vec3f *pos, t_sector *sector,
	size_t index)
{
	t_pickup_object	*pickup_object;

	if (!(pickup_object = ft_memalloc(sizeof(*pickup_object))))
		return (false);
	pickup_object->sector_id = sector->id;
	pickup_object->pos = *pos;
	if (!vector_insert(&env->current_map->pickup_objects, index,
		&pickup_object))
	{
		free(pickup_object);
		return (false);
	}
	return (true);
}

static bool	undo_delete_pickup_object(t_env *env, void *param)
{
	t_rec_del_pickup_event	*tmp;
	t_sector				*tmp_sector;

	tmp = (t_rec_del_pickup_event *)param;
	if (!(tmp_sector = *(t_sector **)map_get(env->current_map->sectors,
		tmp->sector_id)))
		return (false);
	return (insert_pickup_object(env, &tmp->pos, tmp_sector, tmp->index)
		&& change_selection_mode(env, EDITOR_OBJECT));
}

static bool	redo_delete_pickup_object(t_env *env, void *param)
{
	t_rec_del_pickup_event	*tmp;

	tmp = (t_rec_del_pickup_event *)param;
	return ((delete_pickup_object(env, &tmp->pos, false) == 0)
		&& change_selection_mode(env, EDITOR_OBJECT));
}

static bool	delete_event(void *param)
{
	free(param);
	return (false);
}

bool		delete_pickup_object_event(t_env *env, t_vec3f *pos,
	size_t sector_id, size_t index)
{
	t_rec_del_pickup_event	*tmp;

	if (!(tmp = (t_rec_del_pickup_event *)malloc(sizeof(
		t_rec_del_pickup_event))))
		return (false);
	tmp->pos = *pos;
	tmp->sector_id = sector_id;
	tmp->index = index;
	tmp->func.redo = &redo_delete_pickup_object;
	tmp->func.undo = &undo_delete_pickup_object;
	tmp->func.delete = &delete_event;
	if (!record_event(env, REC_EVENT_DEL_PICKUP, (void *)tmp))
		return (delete_event(tmp));
	return (true);
}
