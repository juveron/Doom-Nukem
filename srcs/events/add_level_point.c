/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_level_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 12:45:59 by thboura           #+#    #+#             */
/*   Updated: 2020/07/02 18:19:22 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	undo_level_point(t_env *env, void *param)
{
	t_rec_level_event	*tmp;

	tmp = (t_rec_level_event *)param;
	if (tmp->is_start == true)
		env->current_map->level.start.available = false;
	else
		env->current_map->level.end.available = false;
	return (change_selection_mode(env, EDITOR_LEVELS));
}

static bool	redo_level_point(t_env *env, void *param)
{
	t_rec_level_event	*tmp;
	t_sector			*tmp_sector;

	tmp = (t_rec_level_event *)param;
	if (tmp->is_start)
	{
		tmp_sector = *(t_sector **)map_get(env->current_map->sectors,
			tmp->param.sector_id);
		return (add_start(env, &tmp->param.position, tmp_sector)
			&& change_selection_mode(env, EDITOR_LEVELS));
	}
	else
	{
		tmp_sector = *(t_sector **)map_get(env->current_map->sectors,
			tmp->param.sector_id);
		return (add_end(env, &tmp->param.position, tmp_sector)
			&& change_selection_mode(env, EDITOR_LEVELS));
	}
}

static bool	delete_event(void *param)
{
	free(param);
	return (false);
}

static bool	record_choice(t_env *env, t_rec_level_event *tmp)
{
	if (tmp->is_start)
	{
		if (!record_event(env, REC_EVENT_ADD_START_LEVEL, (void *)tmp))
			return (delete_event(tmp));
	}
	else
	{
		if (!record_event(env, REC_EVENT_ADD_END_LEVEL, (void *)tmp))
			return (delete_event(tmp));
	}
	return (true);
}

bool		add_level_point_event(t_env *env, bool is_start)
{
	t_rec_level_event	*tmp;

	if (!(tmp = (t_rec_level_event *)malloc(sizeof(t_rec_level_event))))
		return (false);
	if (is_start)
		tmp->param = env->current_map->level.start;
	else
		tmp->param = env->current_map->level.end;
	tmp->is_start = is_start;
	tmp->func.redo = &redo_level_point;
	tmp->func.undo = &undo_level_point;
	tmp->func.delete = &delete_event;
	return (record_choice(env, tmp));
}
