/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drag_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:15:39 by thboura           #+#    #+#             */
/*   Updated: 2020/07/14 22:02:44 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

void		cancel_drag_input(t_env *env)
{
	if (env->editor.drag_point.dragged_point->v.v.x != env->editor.drag_point.
		vertex.v.x || env->editor.drag_point.dragged_point->v.v.z != env->
		editor.drag_point.vertex.v.z)
	{
		drag_point(env->editor.drag_point.dragged_point,
			&env->editor.drag_point.vertex);
		env->need_redraw = true;
	}
	env->editor.drag_point.point_is_dragged = false;
	env->editor.drag_point.dragged_point = NULL;
}

static bool	finish_drag(t_env *env)
{
	if ((check_if_already_exists(env, &env->editor.drag_point.dragged_point->v.
		v) || !verify_sector_level_points(env, env->editor.drag_point.
		dragged_point) || !object_out_of_sector(env, env->editor.drag_point.
		dragged_point)))
	{
		drag_point(env->editor.drag_point.dragged_point,
			&env->editor.drag_point.vertex);
	}
	else
	{
		if (!move_point_event(env, env->editor.drag_point.dragged_point,
			env->editor.drag_point.dragged_point->v.v,
			env->editor.drag_point.vertex.v))
			return (false);
	}
	env->need_redraw = true;
	return (true);
}

bool		drag_map_point_input(t_env *env)
{
	if (env->editor.drag_point.point_is_dragged
		&& get_button(SDL_BUTTON_LEFT, NULL))
	{
		env->need_redraw = true;
		drag_point(env->editor.drag_point.dragged_point,
			&env->editor.position_map);
	}
	else if (env->editor.drag_point.point_is_dragged
		&& get_button_up(SDL_BUTTON_LEFT, NULL))
	{
		if (env->editor.drag_point.dragged_point->v.v.x != env->editor.
			drag_point.vertex.v.x || env->editor.drag_point.dragged_point->v.v.
			z != env->editor.drag_point.vertex.v.z)
			if (!finish_drag(env))
				return (false);
		env->editor.drag_point.point_is_dragged = false;
		env->editor.drag_point.dragged_point = NULL;
	}
	return (true);
}
