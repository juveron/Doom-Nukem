/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_level_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 14:54:20 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 18:09:23 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	undo_move_level_point(t_env *env, void *param)
{
	t_rec_move_level_point_event	*tmp;
	t_level_point					*tmp_point;

	tmp = (t_rec_move_level_point_event *)param;
	if (!(tmp_point = get_level_point(&env->current_map->level,
		&tmp->new_point.position)))
		return (false);
	tmp_point->position = tmp->old_point.position;
	tmp_point->sector_id = tmp->old_point.sector_id;
	return (true);
}

static bool	redo_move_level_point(t_env *env, void *param)
{
	t_rec_move_level_point_event	*tmp;
	t_level_point					*tmp_point;

	tmp = (t_rec_move_level_point_event *)param;
	if (!(tmp_point = get_level_point(&env->current_map->level,
		&tmp->old_point.position)))
		return (false);
	tmp_point->position = tmp->new_point.position;
	tmp_point->sector_id = tmp->new_point.sector_id;
	return (true);
}

static bool	delete_event(void *param)
{
	free(param);
	return (false);
}

bool		move_level_point_event(t_env *env, t_level_point *old_point,
	t_level_point *new_point)
{
	t_rec_move_level_point_event	*tmp;

	if (!(tmp = (t_rec_move_level_point_event *)malloc(sizeof(
		t_rec_move_level_point_event))))
		return (false);
	tmp->old_point.position = old_point->position;
	tmp->old_point.sector_id = old_point->sector_id;
	tmp->new_point.position = new_point->position;
	tmp->new_point.sector_id = new_point->sector_id;
	tmp->func.redo = &redo_move_level_point;
	tmp->func.undo = &undo_move_level_point;
	tmp->func.delete = &delete_event;
	if (!record_event(env, REC_EVENT_MOVE_LEVEL_POINT, (void *)tmp))
		return (delete_event(tmp));
	return (true);
}
