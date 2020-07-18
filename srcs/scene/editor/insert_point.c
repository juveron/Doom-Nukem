/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:47:24 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/11 16:04:47 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "editor.h"

static bool	insert_neighbor(t_point *point, t_wall *wall, size_t index)
{
	t_wall	insert_wall;
	t_wall	*tmp_wall;

	tmp_wall = vector_get(&wall->neighbor->walls, index);
	insert_wall = *tmp_wall;
	insert_wall.mtl_bottom = NULL;
	insert_wall.mtl_top = NULL;
	if (!(insert_wall.mtl_top = mtl_create())
		|| !(insert_wall.mtl_bottom = mtl_create()))
		return (false);
	insert_wall.v2 = point;
	tmp_wall->v1 = point;
	if (vector_insert(&wall->neighbor->walls, index, &insert_wall) == false)
		return (false);
	if (!(triangulate_sector(wall->neighbor))
		|| !(triangulate_all_neighbor(wall->neighbor)))
		return (false);
	return (true);
}

static bool	insert_point_p2(t_env *env, t_sector *tmp_sector, t_wall *tmp_wall,
	t_rec_insert_point_event *tmp)
{
	t_wall	*walls;

	walls = tmp_sector->walls.items;
	walls[get_correct_index(tmp_sector->walls.total, tmp->index - 1)]
		.v2 = tmp_wall->v1;
	if (!(vector_insert(&tmp_sector->walls, tmp->index, tmp_wall)))
	{
		free_point(tmp_wall->v1);
		return (false);
	}
	if (!map_add(env->current_map->vertices, tmp_wall->v1->id, &tmp_wall->v1))
	{
		free_point(tmp_wall->v1);
		return (false);
	}
	if (!(triangulate_sector(tmp_sector))
		|| !(triangulate_all_neighbor(tmp_sector)))
		return (false);
	return (true);
}

bool		insert_point(t_env *env, t_point *point, t_wall *wall,
	t_rec_insert_point_event *tmp)
{
	t_wall		tmp_wall;
	t_sector	*tmp_sector;

	tmp_wall = *wall;
	if (!(tmp_wall.v1 = point_clone(point)))
		return (false);
	if (remap_point_id(tmp_wall.v1, env) == false)
	{
		free_point(tmp_wall.v1);
		return (false);
	}
	tmp_sector = *(t_sector **)map_get(env->current_map->sectors,
		wall->sector_id);
	if (tmp->neighbor.active)
	{
		if (!insert_neighbor(tmp_wall.v1, vector_get(&tmp_sector->walls,
			get_correct_index(tmp_sector->walls.total, tmp->index - 1)),
			tmp->neighbor.index))
		{
			free_point(tmp_wall.v1);
			return (false);
		}
	}
	return (insert_point_p2(env, tmp_sector, &tmp_wall, tmp));
}
