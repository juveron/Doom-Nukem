/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_editor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 17:48:53 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/13 03:53:09 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "inputs.h"

static bool	update_2d_mode(t_env *env)
{
	update_notify(env, &env->editor.notify);
	if (!is_over_gui_window(env) && env->main_window->is_over)
	{
		zoom_inputs(env);
		basic_inputs(env, env->ph_context.frame_time);
	}
	get_closest_wall(env);
	set_grid_info(env);
	get_snap_point(env);
	if (get_key(SDL_SCANCODE_K))
		env->need_redraw = true;
	return (true);
}

static bool	update_key_3d(t_env *env)
{
	if (get_key_down(env->shortcuts.editor.gravity))
	{
		env->use_gravity = !env->use_gravity;
		if (env->use_gravity)
		{
			env->player.physic.velocity = vec3f(0, 0, 0);
		}
	}
	if (get_key_down(env->shortcuts.editor.texture))
	{
		if (!selec(env))
			return (false);
	}
	return (true);
}

static bool	update_3d_mode_p2(t_env *env)
{
	if (!set_listener_position(env->player.transform->position)
		|| !set_listener_orientation(camera_forward(&env->camera),
			camera_up(&env->camera)))
		return (false);
	return (true);
}

static bool	update_3d_mode(t_env *env)
{
	env->player.state = 0;
	if (!update_pause_menu(env, &env->gui.pause_menu))
		return (false);
	if (!update_key_3d(env))
		return (false);
	if (env->use_gravity)
	{
		if (get_key_down(env->shortcuts.game.user.jump)
			&& env->player.state & 1 << ST_ON_GROUND)
			env->player.physic.velocity.y = 4;
	}
	if (!ph_loop(&env->ph_context))
		return (false);
	if (env->current_map->level.start.available
		&& env->current_map->level.end.available)
		if (!update_level(env, env->ph_context.dt))
			return (false);
	return (update_3d_mode_p2(env));
}

bool		update_editor(void *param)
{
	t_env *env;

	env = param;
	if (env->app_state == APP_EDITOR)
		update_2d_mode(env);
	if (!update_input(env))
		return (false);
	if (env->app_state != APP_EDITOR)
		update_3d_mode(env);
	if (env->editor.history.available)
		reset_history_window_pos(env, env->editor.history.window);
	return (true);
}
