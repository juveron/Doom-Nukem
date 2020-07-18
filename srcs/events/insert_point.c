/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:54:11 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 17:58:36 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "editor.h"

static bool	undo_insert_point(t_env *env, void *param)
{
	t_rec_insert_point_event	*tmp;
	t_sector					*tmp_sector;
	t_wall						*tmp_walls;

	tmp = (t_rec_insert_point_event *)param;
	tmp_sector = *(t_sector **)map_get(env->current_map->sectors,
		tmp->wall->sector_id);
	tmp_walls = (t_wall *)tmp_sector->walls.items;
	if ((delete_point(env, tmp_walls[tmp->index].v1, false)) == -1)
		return (false);
	return (true);
}

static bool	redo_insert_point(t_env *env, void *param)
{
	t_rec_insert_point_event	*tmp;
	t_wall						wall;

	tmp = (t_rec_insert_point_event *)param;
	wall = *tmp->wall;
	if (wall.neighbor == (t_sector *)-1)
		wall.neighbor = NULL;
	else
		wall.neighbor = *(t_sector **)map_get(env->current_map->sectors,
			(t_u64)wall.neighbor);
	wall.v2 = *(t_point **)map_get(env->current_map->vertices,
		(t_u64)wall.v2);
	if (!(wall.mtl_bottom = mtl_create())
		|| !(wall.mtl_top = mtl_create()))
		return (false);
	mtl_change_diffuse_color(wall.mtl_bottom, get_random_color());
	mtl_change_diffuse_color(wall.mtl_top, get_random_color());
	return (insert_point(env, tmp->point, &wall, tmp));
}

static bool	delete_event(void *param)
{
	t_rec_insert_point_event	*tmp;

	tmp = param;
	point_free(tmp->point);
	free_wall_event(tmp->wall);
	free(tmp);
	return (false);
}

bool		insert_point_event(t_env *env, t_wall *wall, size_t index,
	t_neighbor_handler *neighbor)
{
	t_rec_insert_point_event	*tmp;

	if (!(tmp = (t_rec_insert_point_event *)ft_memalloc(sizeof(
		t_rec_insert_point_event))))
		return (false);
	if (!(tmp->point = point_clone(wall->v1)))
		return (delete_event(tmp));
	if (!(tmp->wall = wall_clone(wall)))
		return (delete_event(tmp));
	tmp->index = index;
	tmp->neighbor.active = neighbor->active;
	if (tmp->neighbor.active)
	{
		tmp->neighbor.index = neighbor->index;
		tmp->neighbor.wall = neighbor->wall;
	}
	tmp->func.undo = &undo_insert_point;
	tmp->func.redo = &redo_insert_point;
	tmp->func.delete = &delete_event;
	if (!record_event(env, REC_EVENT_INSERT_POINT, (void *)tmp))
		return (delete_event(tmp));
	return (true);
}
