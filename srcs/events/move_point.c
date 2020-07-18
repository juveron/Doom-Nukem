/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 14:54:55 by thboura           #+#    #+#             */
/*   Updated: 2020/07/02 18:19:22 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	unrecorded_drag(t_u64 id, t_vec3f *new_pos, t_env *env)
{
	t_point		*point;
	size_t		i;
	t_sector	*sector;

	point = *(t_point **)map_get(env->current_map->vertices, id);
	point->v.v = *new_pos;
	i = 0;
	while (i < point->sector->total)
	{
		sector = *(t_sector **)map_get_index(point->sector, i);
		if (!triangulate_sector(sector))
			return (false);
		++i;
	}
	return (true);
}

static bool	undo_move_point(t_env *env, void *param)
{
	t_rec_move_point_event	*tmp;

	tmp = param;
	return (unrecorded_drag(tmp->point, &tmp->last_pos, env)
		&& change_selection_mode(env, EDITOR_SELECT_POINT));
}

static bool	redo_move_point(t_env *env, void *param)
{
	t_rec_move_point_event	*tmp;

	tmp = param;
	return (unrecorded_drag(tmp->point, &tmp->current_pos, env)
		&& change_selection_mode(env, EDITOR_SELECT_POINT));
}

static bool	delete_event(void *param)
{
	free(param);
	return (false);
}

bool		move_point_event(t_env *env, t_point *point, t_vec3f new_pos,
	t_vec3f old_pos)
{
	t_rec_move_point_event	*tmp;

	if (!(tmp = (t_rec_move_point_event *)malloc(sizeof(
		t_rec_move_point_event))))
		return (false);
	tmp->point = point->id;
	tmp->current_pos = new_pos;
	tmp->last_pos = old_pos;
	tmp->func.redo = &redo_move_point;
	tmp->func.undo = &undo_move_point;
	tmp->func.delete = &delete_event;
	if (!record_event(env, REC_EVENT_MOVE_POINT, (void *)tmp))
		return (delete_event(tmp));
	return (true);
}
