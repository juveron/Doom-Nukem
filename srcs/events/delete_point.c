/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 09:02:24 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 17:25:44 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	undo_delete_point(t_env *env, void *param)
{
	t_point					*tmp_point;
	t_deletion				*tmp_handler;
	t_rec_del_point_event	*tmp;

	tmp = param;
	if (!(tmp_point = point_clone(tmp->point))
		|| !remap_point_id(tmp_point, env)
		|| !map_add(env->current_map->vertices, tmp_point->id, &tmp_point))
	{
		point_free(tmp_point);
		return (false);
	}
	tmp_handler = (t_deletion *)tmp->handler.items;
	return (cancel_point_deletion(env, tmp_handler, tmp->handler.total));
}

static bool	final_deletion(t_sector *sector, t_u64 index, t_wall *wall)
{
	t_wall	*wall_2;

	wall_2 = &wall[get_correct_index(sector->walls.total, index + 1)];
	if (wall[index].neighbor != wall_2->neighbor)
		wall[index].neighbor = NULL;
	free_wall(wall_2);
	if (!vector_delete(&sector->walls, get_correct_index(sector->walls.total,
		index + 1)))
		return (false);
	if (!triangulate_sector(sector))
		return (false);
	return (true);
}

static bool	redo_delete_point(t_env *env, void *param)
{
	size_t					i;
	t_deletion				*tmp_handler;
	t_sector				*tmp_sector;
	t_wall					*tmp_wall;
	t_rec_del_point_event	*tmp;

	tmp = param;
	tmp_handler = (t_deletion *)tmp->handler.items;
	i = 0;
	while (i < tmp->handler.total)
	{
		tmp_sector = *(t_sector **)map_get(env->current_map->sectors,
			tmp_handler[i].sector_id);
		tmp_wall = tmp_sector->walls.items;
		tmp_wall[tmp_handler[i].wall_index].v2 = tmp_wall[get_correct_index(
			tmp_sector->walls.total, tmp_handler[i].wall_index + 2)].v1;
		if (!final_deletion(tmp_sector, tmp_handler[i].wall_index, tmp_wall))
			return (false);
		i++;
	}
	point_free(*(t_point **)map_get(env->current_map->vertices,
			tmp->point->id));
	return (map_delete(env->current_map->vertices, tmp->point->id));
}

static bool	delete_event(void *param)
{
	t_rec_del_point_event	*tmp;
	t_deletion				*del;
	size_t					i;

	tmp = param;
	point_free(tmp->point);
	del = tmp->handler.items;
	i = 0;
	while (i < tmp->handler.total)
	{
		free_wall_event(del[i].wall1);
		free_wall_event(del[i].wall2);
		++i;
	}
	vector_free(&tmp->handler);
	free(tmp);
	return (true);
}

bool		delete_point_event(t_env *env, t_vector *handler, t_point *point)
{
	t_rec_del_point_event	*tmp;

	if (!(tmp = (t_rec_del_point_event *)ft_memalloc(sizeof(
		t_rec_del_point_event))))
		return (false);
	if (!vector_clone(handler, &tmp->handler))
		return (delete_event(tmp));
	if (!(tmp->point = point_clone(point)))
		return (delete_event(tmp));
	tmp->func.undo = &undo_delete_point;
	tmp->func.redo = &redo_delete_point;
	tmp->func.delete = &delete_event;
	if (!record_event(env, REC_EVENT_DEL_POINT, (void *)tmp))
		return (delete_event(tmp));
	return (true);
}
