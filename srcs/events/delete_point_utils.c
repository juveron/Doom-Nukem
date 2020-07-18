/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_point_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:26:03 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 18:26:56 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	correct_deletion(t_env *env, t_sector *tmp_sector,
	t_wall *wall, t_deletion *handler)
{
	t_wall		*tmp_wall;

	if (!vector_insert(&tmp_sector->walls,
		get_correct_index(tmp_sector->walls.total + 1,
			handler->wall_index + 1), wall))
		return (false);
	tmp_wall = tmp_sector->walls.items;
	tmp_wall[handler->wall_index].v2 = *(t_point **)map_get(env->current_map->
		vertices, (size_t)handler->wall1->v2);
	if (handler->wall1->neighbor == (t_sector *)-1)
		tmp_wall[handler->wall_index].neighbor = NULL;
	else
		tmp_wall[handler->wall_index].neighbor = *(t_sector **)map_get(
			env->current_map->sectors, (size_t)handler->wall1->neighbor);
	if (!triangulate_sector(tmp_sector))
		return (false);
	return (true);
}

static bool	set_wall(t_env *env, t_sector *tmp_sector, t_wall *wall,
	t_deletion *deletion)
{
	if (wall->neighbor == (t_sector *)-1)
		wall->neighbor = NULL;
	else
	{
		wall->neighbor = *(t_sector **)map_get(env->current_map->sectors,
			(size_t)wall->neighbor);
	}
	wall->v1 = *(t_point **)map_get(env->current_map->vertices,
		(size_t)wall->v1);
	wall->v2 = *(t_point **)map_get(env->current_map->vertices,
		(size_t)wall->v2);
	if (!(wall->mtl_bottom = mtl_clone(wall->mtl_bottom)))
		return (false);
	if (!(wall->mtl_top = mtl_clone(wall->mtl_top)))
		return (false);
	return (correct_deletion(env, tmp_sector, wall, deletion));
}

bool		cancel_point_deletion(t_env *env, t_deletion *handler,
	size_t total)
{
	size_t		i;
	t_sector	*tmp_sector;
	t_wall		wall;

	i = 0;
	while (i < total)
	{
		tmp_sector = *(t_sector **)map_get(env->current_map->sectors,
			handler[i].sector_id);
		wall = *handler[i].wall2;
		if (!set_wall(env, tmp_sector, &wall, &handler[i]))
			return (false);
		i++;
	}
	return (true);
}
