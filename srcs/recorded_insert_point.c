/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recorded_insert_point.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 10:34:44 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/04 14:51:56 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static bool	record_neighbor(t_neighbor_handler *neighbor,
	t_point *new_point, t_wall *wall)
{
	t_wall		insert_wall;
	t_wall		*tmp_wall;

	neighbor->active = true;
	if (!(tmp_wall = get_wall_by_position(wall, wall->neighbor,
		&neighbor->index)))
		return (false);
	insert_wall = *tmp_wall;
	insert_wall.mtl_bottom = NULL;
	insert_wall.mtl_top = NULL;
	if (!(insert_wall.mtl_top = mtl_create())
		|| !(insert_wall.mtl_bottom = mtl_create()))
		return (false);
	mtl_change_diffuse_color(insert_wall.mtl_top, get_random_color());
	mtl_change_diffuse_color(insert_wall.mtl_bottom, get_random_color());
	insert_wall.v2 = new_point;
	tmp_wall->v1 = new_point;
	if (vector_insert(&wall->neighbor->walls, neighbor->index,
		&insert_wall) == false)
		return (false);
	if (!(triangulate_sector(wall->neighbor))
		|| !(triangulate_all_neighbor(wall->neighbor)))
		return (false);
	return (true);
}

bool		free_error(t_wall *wall)
{
	free_point(wall->v1);
	free_wall(wall);
	return (false);
}

static bool	insert_wall(t_env *env, t_wall *wall, t_sector *sector)
{
	size_t				i;
	t_neighbor_handler	neighbor;

	ft_bzero(&neighbor, sizeof(neighbor));
	if (env->editor.closest->neighbor
		&& !record_neighbor(&neighbor, wall->v1, env->editor.closest))
		return (free_error(wall));
	env->editor.closest->v2 = wall->v1;
	i = 0;
	if (!insert_by_correct_wall(env->editor.closest, wall, sector, &i))
		return (free_error(wall));
	if (!(triangulate_sector(sector))
		|| !(triangulate_all_neighbor(sector)))
		return (free_error(wall));
	return (insert_point_event(env, wall, i + 1, &neighbor));
}

static bool	recorded_insert_point_p2(t_wall *tmp_wall, t_sector *tmp_sector,
		t_env *env)
{
	if (!(tmp_wall->mtl_bottom = mtl_create())
		|| !(tmp_wall->mtl_top = mtl_create()))
		return (free_error(tmp_wall));
	mtl_change_diffuse_color(tmp_wall->mtl_bottom, get_random_color());
	mtl_change_diffuse_color(tmp_wall->mtl_top, get_random_color());
	if (!map_add(tmp_wall->v1->sector, tmp_sector->id, &tmp_sector))
		return (free_error(tmp_wall));
	if (tmp_wall->neighbor)
	{
		if (!map_add(tmp_wall->v1->sector, tmp_wall->neighbor->id,
				&tmp_wall->neighbor))
			return (free_error(tmp_wall));
	}
	if (!map_add(env->current_map->vertices, tmp_wall->v1->id, &tmp_wall->v1))
		return (free_error(tmp_wall));
	return (insert_wall(env, tmp_wall, tmp_sector));
}

bool		recorded_insert_point(t_env *env)
{
	t_sector	*tmp_sector;
	t_wall		tmp_wall;

	tmp_wall = *env->editor.closest;
	tmp_wall.mtl_bottom = NULL;
	tmp_wall.mtl_top = NULL;
	if (!(tmp_wall.v1 = (t_point *)ft_memalloc(sizeof(t_point))))
		return (false);
	tmp_wall.v1->v = env->editor.position_map;
	tmp_wall.v1->id = env->editor.unique_id_vertices++;
	if (!(tmp_wall.v1->sector = map_init(sizeof(t_sector *))))
		return (free_error(&tmp_wall));
	tmp_sector = *(t_sector **)map_get(env->current_map->sectors,
		env->editor.closest->sector_id);
	return (recorded_insert_point_p2(&tmp_wall, tmp_sector, env));
}
