/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:46:36 by thboura           #+#    #+#             */
/*   Updated: 2020/07/15 23:03:09 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

static void	editor_3d_player_inputs(t_env *env, float dt)
{
	if (get_key(env->shortcuts.game.user.move_up))
	{
		env->player.physic.velocity = vec3f(0, 0, 0);
		env->player.new_pos.y += -12.0f * dt * (float)(env->player.speed + 1);
	}
	if (get_key(env->shortcuts.game.user.move_down))
	{
		env->player.physic.velocity = vec3f(0, 0, 0);
		env->player.new_pos.y += 12.0f * dt * (float)(env->player.speed + 1);
	}
}

static void	player_inputs_p2(t_env *env, float dt)
{
	if (env->app_state == APP_EDITOR_GAME)
		editor_3d_player_inputs(env, dt);
	if (env->use_gravity)
	{
		if (get_key_down(env->shortcuts.game.user.jump)
			&& env->player.state & 1 << ST_ON_GROUND)
			env->player.physic.velocity.y = 4;
		if (get_key(env->shortcuts.game.user.crouch))
			env->player.height = CROUCH_HEIGHT;
		else
			env->player.height = PLAYER_HEIGHT;
	}
	if (get_key(env->shortcuts.game.user.sprint))
		env->player.speed = true;
	if (get_key_up(env->shortcuts.game.user.sprint))
		env->player.speed = false;
}

void		player_inputs(t_env *env, float dt, t_vec3f *look_dir)
{
	if (get_key(env->shortcuts.game.user.move_forward))
	{
		env->player.new_pos = vec3f_add(env->player.new_pos,
			vec3f_mul(*look_dir, (float)(env->player.speed + 1)));
	}
	if (get_key(env->shortcuts.game.user.move_back))
	{
		env->player.new_pos = vec3f_sub(env->player.new_pos,
			vec3f_mul(*look_dir, (float)(env->player.speed + 1)));
	}
	if (get_key(env->shortcuts.game.user.move_left))
	{
		env->player.new_pos.x += look_dir->z * (float)(env->player.speed + 1);
		env->player.new_pos.y += 0 * (float)(env->player.speed + 1);
		env->player.new_pos.z += -look_dir->x * (float)(env->player.speed + 1);
	}
	if (get_key(env->shortcuts.game.user.move_right))
	{
		env->player.new_pos.x += -look_dir->z * (float)(env->player.speed + 1);
		env->player.new_pos.y += 0 * (float)(env->player.speed + 1);
		env->player.new_pos.z += look_dir->x * (float)(env->player.speed + 1);
	}
	player_inputs_p2(env, dt);
}
