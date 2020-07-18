/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closest_wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 15:30:51 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/06 15:32:38 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void		update_closest_wall(t_env *env, t_wall *wall, float *dist)
{
	t_vec2f		a;
	t_vec2f		b;
	t_vec2f		tmp;
	float		dist2;

	a = (t_vec2f){env->editor.position_map.v.x
		- wall->v1->v.v.x, env->editor.position_map.v.z
		- wall->v1->v.v.z};
	b = (t_vec2f){wall->v2->v.v.x
		- wall->v1->v.v.x, wall->v2->v.v.z
		- wall->v1->v.v.z};
	tmp = vec2f_project(a, b);
	dist2 = fabsf(a.x - tmp.x) + fabsf(a.y - tmp.y);
	if (dist2 < *dist)
	{
		if (vec2f_length(tmp) < vec2f_length(b) && vec2f_dot(a, b) >= 0)
		{
			*dist = dist2;
			env->editor.closest = wall;
		}
	}
}

void			get_closest_wall(t_env *env)
{
	float		dist;
	t_sector	*sector;
	t_wall		*walls;
	size_t		i;
	size_t		j;

	i = 0;
	dist = 1.f;
	env->editor.closest = NULL;
	while (i < env->current_map->sectors->total)
	{
		sector = *(t_sector **)map_get_index(env->current_map->sectors, i);
		walls = sector->walls.items;
		j = 0;
		while (j < sector->walls.total)
			update_closest_wall(env, &walls[j++], &dist);
		i++;
	}
}
