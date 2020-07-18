/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_game_inputs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:45:41 by thboura           #+#    #+#             */
/*   Updated: 2020/07/13 03:08:26 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

static void	basic_game_inputs(t_env *env, float dt)
{
	t_vec3f			look_dir;
	t_matrix4		m_rot;

	matrix_rotation(0, env->camera.transform.rotation.y, 0, &m_rot);
	mul_matrix4_vec3f(&(t_vec3f){0, 0, -1}, &look_dir, &m_rot);
	look_dir = vec3f_mul(look_dir, 5.f * dt);
	player_inputs(env, dt, &look_dir);
}

bool		global_movement_ph_inputs(t_env *env, float dt)
{
	if (!env->main_window->is_over || env->gui.status == GUI_PAUSE)
		return (true);
	basic_game_inputs(env, dt);
	return (true);
}

bool		global_game_inputs(t_env *env)
{
	int				tmp;

	tmp = pause_game_inputs(env);
	if (tmp == -1)
		return (false);
	else if (!env->main_window->is_over || tmp == 1)
		return (true);
	if (env->gui.status == GUI_NONE)
	{
		rotation_game_inputs(env, &env->global_option);
	}
	return (true);
}

bool		global_game_editor_inputs(t_env *env)
{
	int				tmp;

	tmp = pause_editor_inputs(env);
	if (tmp == -1)
		return (false);
	else if (!env->main_window->is_over || tmp == 1)
		return (true);
	rotation_inputs(env, &env->global_option);
	return (true);
}
