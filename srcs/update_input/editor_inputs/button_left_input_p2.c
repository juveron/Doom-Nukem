/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_left_input_p2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 08:54:33 by thboura           #+#    #+#             */
/*   Updated: 2020/07/14 22:12:13 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

static bool	get_state_for_input(t_env *env)
{
	if (env->editor.state.global_state == EDITOR_IDLE)
	{
		if (!vector_init(&env->editor.tmp_vertices, sizeof(t_point *)))
			return (false);
		if (!(env->editor.tmp_sector = ft_memalloc(sizeof(t_sector))))
		{
			vector_free(&env->editor.tmp_vertices);
			return (false);
		}
		env->editor.tmp_sector->id = env->editor.unique_id_sectors++;
		if (!vector_init(&env->editor.tmp_sector->walls, sizeof(t_wall)))
		{
			free(env->editor.tmp_sector);
			vector_free(&env->editor.tmp_vertices);
			return (false);
		}
		env->editor.tmp_sector->walls.total = 0;
		env->editor.state.global_state = EDITOR_MAKE_SECTOR;
	}
	if (env->editor.state.global_state == EDITOR_MAKE_SECTOR)
		if (!add_point_tmp(env))
			return (false);
	return (true);
}

bool		line_input(t_env *env)
{
	if (check_if_already_exists(env, &env->editor.position_map.v))
		send_notify("Position already taken.", 0xFF0000, env);
	else
	{
		if (check_multiple_points(env))
			send_notify("Multiple points on this position.", 0xFF0000, env);
		else
			return (get_state_for_input(env));
	}
	return (true);
}

void		point_input(t_env *env)
{
	get_dragged_point(env);
	if (env->editor.drag_point.point_is_dragged)
	{
		env->editor.drag_point.point_selected = env->editor.drag_point.
			dragged_point;
		ft_snprintf(env->buff, sizeof(env->buff), "%lu", env->editor.
			drag_point.dragged_point->id);
		send_notify(env->buff, 0x00FF00, env);
	}
	else
		send_notify("No point selected.", 0xFF0000, env);
}

bool		level_input(t_env *env)
{
	get_dragged_point(env);
	if (env->editor.drag_point.point_is_dragged)
		send_notify("Point already used.", 0xFF0000, env);
	else
	{
		if (get_key(env->shortcuts.editor.level_point.start)
			&& !get_key(env->shortcuts.editor.level_point.end))
		{
			return (add_level_point(env, &env->editor.position_map.v, true,
				true));
		}
		if (get_key(env->shortcuts.editor.level_point.end)
			&& !get_key(env->shortcuts.editor.level_point.start))
		{
			return (add_level_point(env, &env->editor.position_map.v, false,
				true));
		}
	}
	return (true);
}

bool		object_input(t_env *env)
{
	get_dragged_point(env);
	if (env->editor.drag_point.point_is_dragged)
		send_notify("Point already used.", 0xFF0000, env);
	else
	{
		if (add_pickup_object(env, &env->editor.position_map.v, true) == 2)
			return (false);
	}
	return (true);
}
