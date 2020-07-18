/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drag_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 17:56:44 by thboura           #+#    #+#             */
/*   Updated: 2020/06/05 17:57:14 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_u32		get_dragged_point(t_env *env)
{
	t_point	*v;
	t_u32	i;

	i = 0;
	while (i < env->current_map->vertices->total)
	{
		v = *(t_point **)map_get_index(env->current_map->vertices, i);
		if (v->v.v.x == env->editor.position_map.v.x
			&& v->v.v.z == env->editor.position_map.v.z)
		{
			if (!env->editor.drag_point.point_is_dragged)
				env->editor.drag_point.vertex = v->v;
			env->editor.drag_point.point_is_dragged = true;
			env->editor.drag_point.dragged_point = v;
			return (i);
		}
		i++;
	}
	env->editor.drag_point.point_is_dragged = false;
	return (0);
}

void		drag_point(t_point *point, t_vertex *new_pos)
{
	size_t		i;
	t_sector	*sector;

	if (point->v.v.x != new_pos->v.x || point->v.v.z != new_pos->v.z)
	{
		point->v = *new_pos;
		point->v.v_texture.x = new_pos->v.x;
		point->v.v_texture.y = new_pos->v.z;
		i = 0;
		while (i < point->sector->total)
		{
			sector = *(t_sector **)map_get_index(point->sector, i);
			if (sector->has_roof)
				vector_free(&sector->triangle_top);
			vector_free(&sector->triangle_bottom);
			triangulate_sector(sector);
			i++;
		}
	}
}

t_sector	*is_in_sector(t_env *env, t_vec2f *pos, bool edge)
{
	t_sector	*sector;
	size_t		i;

	i = 0;
	while (i < env->current_map->sectors->total)
	{
		sector = *(t_sector **)map_get_index(env->current_map->sectors, i);
		if (inside(pos, sector, edge))
			return (sector);
		i++;
	}
	return (NULL);
}
