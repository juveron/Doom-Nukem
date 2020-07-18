/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 17:55:05 by thboura           #+#    #+#             */
/*   Updated: 2020/06/24 11:10:18 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	resume_settings_menu(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	disable_current_option(&env->gui.settings_menu);
	env->gui.settings_menu.container->component.is_visible = false;
	env->app_state = env->gui.settings_menu.prev_app_state;
	if (env->gui.settings_menu.prev_gui_status == GUI_PAUSE)
	{
		if (env->app_state == APP_GAME)
			init_game_pause(env);
		else
			init_pause_menu(env);
	}
	else if (env->gui.settings_menu.prev_gui_status == GUI_MAIN_MENU)
		env->gui.main_menu.container->component.is_visible = true;
	env->gui.status = env->gui.settings_menu.prev_gui_status;
	env->main_window->main_container->component.need_redraw = true;
	return (true);
}

bool	exit_settings_menu(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	resume_settings_menu(env);
	if (env->gui.status == GUI_PAUSE)
	{
		if (env->app_state == APP_GAME)
		{
			if (!resume_game_pause(env))
				return (false);
		}
		else
		{
			if (!resume_pause_menu(env))
				return (false);
		}
	}
	return (true);
}
