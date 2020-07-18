/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:46:42 by thboura           #+#    #+#             */
/*   Updated: 2020/06/12 10:47:30 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

void	rotation_inputs(t_env *env, t_global_option *option)
{
	if (get_button_down(SDL_BUTTON_RIGHT, NULL) && !is_over_gui_window(env))
		SDL_SetRelativeMouseMode(true);
	if (get_button(SDL_BUTTON_RIGHT, NULL) && SDL_GetRelativeMouseMode())
	{
		env->camera.transform.rotation.x = clampf(env->camera.transform.
			rotation.x + -get_mouse_position_delta().y *
			option->mouse_sensibility, -90, 90);
		env->camera.transform.rotation.y += get_mouse_position_delta().x *
			option->mouse_sensibility;
	}
	else if (get_button_up(SDL_BUTTON_RIGHT, NULL))
		SDL_SetRelativeMouseMode(false);
}

void	rotation_game_inputs(t_env *env, t_global_option *option)
{
	if (SDL_GetRelativeMouseMode())
	{
		env->camera.transform.rotation.x = clampf(env->camera.transform.
			rotation.x + -get_mouse_position_delta().y *
			option->mouse_sensibility, -90, 90);
		env->camera.transform.rotation.y += get_mouse_position_delta().x *
			option->mouse_sensibility;
	}
}
