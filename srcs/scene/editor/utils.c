/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 14:37:06 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/01 14:37:22 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_vec2i	grid_to_win(t_vec3f *vec, t_env *env)
{
	return (vec2i(vec->x * env->editor.zoom + env->editor.offset_z.x,
		vec->z * env->editor.zoom + env->editor.offset_z.y));
}

t_u64	get_correct_index(t_u64 n, t_s64 di)
{
	return ((di + n) % n);
}

t_vec2f	win_to_map(t_vec2i *win_pos, t_env *env)
{
	t_vec2f	map_pos;

	map_pos.x = win_pos->x / (env->editor.subdiv * env->editor.div)
			- env->editor.offset.x;
	map_pos.y = win_pos->y / (env->editor.subdiv * env->editor.div)
			- env->editor.offset.y;
	return (map_pos);
}

t_wall	*get_wall_by_position(t_wall *closest, t_sector *sector,
	size_t *index)
{
	t_wall	*walls;

	*index = 0;
	walls = (t_wall *)sector->walls.items;
	while (*index < sector->walls.total)
	{
		if (walls[*index].v1->v.v.x == closest->v2->v.v.x
			&& walls[*index].v1->v.v.z == closest->v2->v.v.z
			&& walls[*index].v2->v.v.x == closest->v1->v.v.x
			&& walls[*index].v2->v.v.z == closest->v1->v.v.z)
			return (&walls[*index]);
		(*index)++;
	}
	return (NULL);
}
