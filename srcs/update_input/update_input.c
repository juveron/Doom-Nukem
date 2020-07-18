/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:46:51 by thboura           #+#    #+#             */
/*   Updated: 2020/07/13 03:07:44 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

static bool	update_menu_input(t_env *env)
{
	if (env->app_state == APP_SETTINGS)
	{
		if (!global_settings_inputs(env))
			return (false);
	}
	else if (env->app_state == APP_MAIN_MENU)
	{
		if (!global_main_menu_inputs(env))
			return (false);
	}
	return (true);
}

bool		update_input(t_env *env)
{
	if (env->app_state == APP_EDITOR && !is_over_gui_window(env))
	{
		if (!global_editor_inputs(env))
			return (false);
	}
	else if (env->app_state == APP_EDITOR_GAME)
	{
		if (!global_game_editor_inputs(env))
			return (false);
	}
	else if (env->app_state == APP_GAME)
	{
		if (!global_game_inputs(env))
			return (false);
	}
	else if (env->app_state == APP_GAME_OVER)
	{
		if (!game_over_inputs(env))
			return (false);
	}
	else
		return (update_menu_input(env));
	return (true);
}
