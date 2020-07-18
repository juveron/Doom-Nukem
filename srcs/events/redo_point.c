/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redo_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:24:17 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 17:25:11 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "editor.h"

static bool	re_add_point_tmp_p2(t_wall *tmp, t_point **point_tmp, t_env *env,
	t_point *position)
{
	ft_bzero(tmp, sizeof(t_wall));
	if (!(*point_tmp = point_clone(position)))
		return (false);
	if (!point_add_sector(*point_tmp, env->editor.tmp_sector))
	{
		free_point(*point_tmp);
		return (false);
	}
	if (!vector_push(&env->editor.tmp_vertices, point_tmp))
	{
		free_point(*point_tmp);
		return (false);
	}
	return (true);
}

static bool	re_add_point_tmp_p3(t_point **point, t_wall *tmp, t_env *env,
	t_point *point_tmp)
{
	t_wall		*walls;

	walls = vector_get(&env->editor.tmp_sector->walls, 0);
	walls[env->editor.tmp_sector->walls.total - 1].v2 = point[env->editor.
		tmp_vertices.total - 1];
	tmp->v1 = walls[env->editor.tmp_sector->walls.total - 1].v2;
	if (!vector_push(&env->editor.tmp_sector->walls, tmp))
	{
		free_point(point_tmp);
		return (false);
	}
	return (true);
}

static bool	re_add_point_tmp(t_env *env, t_point *position)
{
	t_point		**point;
	t_point		*point_tmp;
	t_wall		tmp;

	if (!re_add_point_tmp_p2(&tmp, &point_tmp, env, position))
		return (false);
	point = vector_get(&env->editor.tmp_vertices, 0);
	if (env->editor.tmp_sector->walls.total == 0)
	{
		tmp.v1 = point[env->editor.tmp_vertices.total - 1];
		if (!vector_push(&env->editor.tmp_sector->walls, &tmp))
		{
			free_point(point_tmp);
			return (false);
		}
	}
	else
	{
		if (!re_add_point_tmp_p3(point, &tmp, env, point_tmp))
			return (false);
	}
	return (true);
}

static bool	clean_error(t_env *env)
{
	if (env->editor.tmp_sector)
		free(env->editor.tmp_sector);
	vector_free(&env->editor.tmp_vertices);
	vector_free(&env->editor.tmp_sector->walls);
	return (false);
}

bool		redo_point(t_env *env, void *param)
{
	t_rec_add_point_event	*position;

	position = param;
	if (!change_selection_mode(env, EDITOR_SELECT_LINE))
		return (false);
	if (env->editor.state.global_state == EDITOR_IDLE)
	{
		if (!(env->editor.tmp_sector = ft_memalloc(sizeof(t_sector)))
			|| !vector_init(&env->editor.tmp_vertices, sizeof(t_point *))
			|| !vector_init(&env->editor.tmp_sector->walls, sizeof(t_wall)))
			return (clean_error(env));
		env->editor.tmp_sector->id = env->editor.unique_id_sectors++;
		env->editor.tmp_sector->walls.total = 0;
		env->editor.state.global_state = EDITOR_MAKE_SECTOR;
		env->editor.state.section_state = EDITOR_SELECT_LINE;
	}
	++env->editor.unique_id_vertices;
	if (!re_add_point_tmp(env, position->position))
		return (clean_error(env));
	send_notify("Readded previous point.", 0xFFFFFF, env);
	return (true);
}
