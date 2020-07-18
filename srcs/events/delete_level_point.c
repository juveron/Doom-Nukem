/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_level_point.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 19:12:49 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 17:32:45 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	undo_delete_level_point(t_env *env, void *param)
{
	t_rec_del_level_point_event	*tmp;

	tmp = param;
	if (tmp->is_start)
	{
		env->current_map->level.start.position = tmp->point.position;
		env->current_map->level.start.sector_id = tmp->point.sector_id;
		env->current_map->level.start.available = true;
	}
	else
	{
		env->current_map->level.end.position = tmp->point.position;
		env->current_map->level.end.sector_id = tmp->point.sector_id;
		env->current_map->level.end.available = true;
	}
	return (true);
}

static bool	redo_delete_level_point(t_env *env, void *param)
{
	t_rec_del_level_point_event	*tmp;

	tmp = param;
	return (delete_level_point(env, get_level_point(&env->
		current_map->level, &tmp->point.position), false));
}

static bool	delete_event(void *param)
{
	free(param);
	return (false);
}

bool		delete_level_point_event(t_env *env, t_level_point *point,
	bool is_start)
{
	t_rec_del_level_point_event	*tmp;

	if (!(tmp = (t_rec_del_level_point_event *)malloc(sizeof(
		t_rec_del_level_point_event))))
		return (false);
	tmp->point.position = point->position;
	tmp->point.sector_id = point->sector_id;
	tmp->is_start = is_start;
	tmp->func.undo = &undo_delete_level_point;
	tmp->func.redo = &redo_delete_level_point;
	tmp->func.delete = &delete_event;
	if (!record_event(env, REC_EVENT_DEL_LEVEL_POINT, (void *)tmp))
		return (delete_event(tmp));
	return (true);
}
