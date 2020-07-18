/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_options_p5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:37:35 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 17:42:29 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		change_crouch_key(t_env *env, SDL_Scancode input_scancode)
{
	return (reset_control_key(env,
		env->gui.settings_menu.controls.crouch_button,
		&env->shortcuts.game.user.crouch, input_scancode));
}

bool		change_sprint_key(t_env *env, SDL_Scancode input_scancode)
{
	return (reset_control_key(env,
		env->gui.settings_menu.controls.sprint_button,
		&env->shortcuts.game.user.sprint, input_scancode));
}

bool		change_jump_key(t_env *env, SDL_Scancode input_scancode)
{
	return (reset_control_key(env,
		env->gui.settings_menu.controls.jump_button,
		&env->shortcuts.game.user.jump, input_scancode));
}

bool		change_move_down_key(t_env *env, SDL_Scancode input_scancode)
{
	return (reset_control_key(env,
		env->gui.settings_menu.controls.
		move_down_button, &env->shortcuts.game.user.move_down, input_scancode));
}
