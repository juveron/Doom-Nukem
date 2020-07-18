/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_options_p4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:37:39 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 17:41:25 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		change_move_up_key(t_env *env, SDL_Scancode input_scancode)
{
	return (reset_control_key(env, env->gui.settings_menu.controls.
		move_up_button, &env->shortcuts.game.user.move_up, input_scancode));
}

bool		change_move_right_key(t_env *env, SDL_Scancode input_scancode)
{
	return (reset_control_key(env, env->gui.settings_menu.controls.
		move_right_button, &env->shortcuts.game.user.move_right,
		input_scancode));
}

bool		change_move_left_key(t_env *env, SDL_Scancode input_scancode)
{
	return (reset_control_key(env, env->gui.settings_menu.controls.
		move_left_button, &env->shortcuts.game.user.move_left, input_scancode));
}

bool		change_move_back_key(t_env *env, SDL_Scancode input_scancode)
{
	return (reset_control_key(env, env->gui.settings_menu.controls.
		move_back_button, &env->shortcuts.game.user.move_back, input_scancode));
}

bool		change_move_forward_key(t_env *env, SDL_Scancode input_scancode)
{
	return (reset_control_key(env, env->gui.settings_menu.controls.
		move_forward_button, &env->shortcuts.game.user.move_forward,
		input_scancode));
}
