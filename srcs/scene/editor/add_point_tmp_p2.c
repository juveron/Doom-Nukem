/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_point_tmp_p2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:41:51 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/01 12:42:23 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "editor.h"

bool	vaild_wall_position(t_vec3f *v1, t_vec3f *v2, t_env *env)
{
	t_sector	*sectors;
	t_wall		*walls;
	size_t		i;
	size_t		j;

	i = 0;
	while (i < env->current_map->sectors->total)
	{
		sectors = *(t_sector **)map_get_index(env->current_map->sectors, i);
		walls = sectors->walls.items;
		j = 0;
		while (j < sectors->walls.total)
		{
			if (walls[j].neighbor != NULL && ((walls[j].v1->v.v.x == v1->x
				&& walls[j].v1->v.v.z == v1->z && walls[j].v2->v.v.x == v2->x
				&& walls[j].v2->v.v.z == v2->z) || (walls[j].v1->v.v.x == v2->x
				&& walls[j].v1->v.v.z == v2->z && walls[j].v2->v.v.x == v1->x
				&& walls[j].v2->v.v.z == v1->z)))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	close_sector(t_env *env, t_wall *tmp, t_wall *walls, size_t j)
{
	if (env->editor.tmp_sector->walls.total > 2 && j == 0)
	{
		tmp->v1 = *(t_point **)vector_get(&env->editor.tmp_vertices,
			env->editor.tmp_vertices.total - 1);
		walls[env->editor.tmp_sector->walls.total - 1].v2 = walls[0].v1;
		if (!vaild_wall_position(&tmp->v1->v.v, &walls[0].v1->v.v, env))
		{
			send_notify("ERROR: You can't draw over \
							portal wall !", 0xFF0000, env);
			return (true);
		}
		if (!add_sector_event(env))
			return (false);
		if (!convert_sector(env->editor.tmp_sector, &env->editor.tmp_vertices,
			env))
			return (false);
		env->editor.state.global_state = EDITOR_IDLE;
	}
	return (true);
}
