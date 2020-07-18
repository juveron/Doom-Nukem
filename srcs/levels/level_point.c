/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 12:28:40 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 15:47:47 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "internal_handler.h"

static void	add_level_point_p2(t_env *env, t_sector *tmp_sector,
	t_move_handler *handler, t_add_level_handler *tmp_handler)
{
	if (tmp_handler->is_start)
	{
		handler->saved_point = env->current_map->level.start;
		tmp_handler->ret = add_start(env, tmp_handler->position, tmp_sector);
		tmp_handler->new_pos = env->current_map->level.start;
	}
	else
	{
		handler->saved_point = env->current_map->level.end;
		tmp_handler->ret = add_end(env, tmp_handler->position, tmp_sector);
		tmp_handler->new_pos = env->current_map->level.end;
	}
}

static void	set_add_level_handler(t_add_level_handler *handler, bool is_start,
	t_vec3f *position)
{
	handler->is_start = is_start;
	handler->position = position;
}

bool		add_level_point(t_env *env, t_vec3f *position, bool is_start,
	bool record)
{
	t_sector			*tmp_sector;
	t_move_handler		handler;
	t_add_level_handler	tmp_handler;

	if (!(tmp_sector = is_in_sector(env, &(t_vec2f){env->editor.
		position_map.v.x, env->editor.position_map.v.z}, false)))
	{
		send_notify("Start / End of level must be inside a sector.", 0xFF0000,
			env);
		return (true);
	}
	set_add_level_handler(&tmp_handler, is_start, position);
	add_level_point_p2(env, tmp_sector, &handler, &tmp_handler);
	if (tmp_handler.ret && record)
	{
		if (handler.saved_point.available)
			return (move_level_point_event(env, &handler.saved_point,
				&tmp_handler.new_pos));
		else
			return (add_level_point_event(env, is_start));
	}
	return (true);
}

void		move_level_point(t_env *env, t_move_handler *handler)
{
	t_level_point	*tmp_point;

	if (!handler->active)
	{
		if (!(tmp_point = get_level_point(&env->current_map->level,
			&env->editor.position_map.v)))
			return ;
		handler->saved_point.position = tmp_point->position;
		handler->saved_point.sector_id = tmp_point->sector_id;
		handler->dragged_point = tmp_point;
		handler->active = true;
	}
	handler->dragged_point->position.x = env->editor.position_map.v.x;
	handler->dragged_point->position.z = env->editor.position_map.v.z;
}
