/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_point_tmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:41:40 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/01 12:41:40 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "editor.h"

static bool	add_point_p2(t_env *env, t_wall *tmp, t_wall *walls)
{
	tmp->v1 = *(t_point **)vector_get(&env->editor.tmp_vertices,
		env->editor.tmp_vertices.total - 2);
	walls[env->editor.tmp_sector->walls.total - 1].v2 = *(t_point **)
		vector_get(&env->editor.tmp_vertices,
		env->editor.tmp_vertices.total - 1);
	if (!vaild_wall_position(&tmp->v1->v.v, &env->editor.position_map.v,
		env))
	{
		if (!vector_delete(&env->editor.tmp_vertices,
			env->editor.tmp_vertices.total - 1))
			return (false);
		send_notify("ERROR: You can't draw over \
			portal wall !", 0xFF0000, env);
		return (true);
	}
	tmp->v1 = walls[env->editor.tmp_sector->walls.total - 1].v2;
	tmp->sector_id = env->editor.tmp_sector->id;
	if (!vector_push(&env->editor.tmp_sector->walls, tmp))
		return (false);
	return (true);
}

static bool	add_point_p3(t_env *env, t_wall *tmp, t_wall *walls, t_point *point)
{
	if (!vector_push(&env->editor.tmp_vertices, &point))
	{
		free_point(point);
		return (false);
	}
	if (env->editor.tmp_sector->walls.total == 0)
	{
		tmp->v1 = *(t_point **)vector_get(&env->editor.tmp_vertices,
			env->editor.tmp_vertices.total - 1);
		tmp->sector_id = env->editor.tmp_sector->id;
		if (!vector_push(&env->editor.tmp_sector->walls, tmp))
			return (false);
	}
	else
	{
		if (!add_point_p2(env, tmp, walls))
			return (false);
	}
	if (!add_point_event(env, point))
		return (false);
	return (true);
}

static bool	add_point(t_env *env, t_wall *tmp, t_wall *walls)
{
	t_point	*point;

	if (!(point = malloc(sizeof(t_point))))
		return (false);
	if (!(point->sector = map_init(sizeof(t_sector *))))
	{
		free_point(point);
		return (false);
	}
	point->v = env->editor.position_map;
	point->id = env->editor.unique_id_vertices++;
	if (!point_add_sector(point, env->editor.tmp_sector))
	{
		free_point(point);
		return (false);
	}
	return (add_point_p3(env, tmp, walls, point));
}

static bool	check_pos(t_env *env, t_wall *walls, t_wall *tmp)
{
	size_t	j;
	bool	exist;

	exist = false;
	j = 0;
	while (j < env->editor.tmp_sector->walls.total)
	{
		if (walls[j].v1->v.v.x == env->editor.position_map.v.x
			&& walls[j].v1->v.v.z == env->editor.position_map.v.z)
		{
			close_sector(env, tmp, walls, j);
			exist = true;
		}
		j++;
	}
	if (j != 0 && j != env->editor.tmp_sector->walls.total
			&& (walls[j - 1].v2->v.v.x == env->editor.position_map.v.x
			&& walls[j - 1].v2->v.v.z == env->editor.position_map.v.z))
		exist = true;
	return (exist);
}

bool		add_point_tmp(t_env *env)
{
	t_wall	*walls;
	t_wall	tmp;
	bool	exist;

	ft_bzero(&tmp, sizeof(t_wall));
	walls = env->editor.tmp_sector->walls.items;
	exist = check_pos(env, walls, &tmp);
	if (!exist)
		return (add_point(env, &tmp, walls));
	return (true);
}
