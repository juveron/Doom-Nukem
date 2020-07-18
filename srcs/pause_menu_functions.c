/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:22:43 by thboura           #+#    #+#             */
/*   Updated: 2020/06/27 17:39:32 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		resume_pause_menu(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	env->gui.pause_menu.container->component.is_visible = false;
	env->main_window->main_container->component.need_redraw = true;
	env->gui.status = GUI_NONE;
	env->time_scale = 1.f;
	if (!change_source_state(env->sound_manager.audio_gui.open_pause_menu.
		source, SRC_STOP))
		return (false);
	if (!change_source_state(env->sound_manager.audio_gui.close_pause_menu.
		source, SRC_PLAY))
		return (false);
	if (!init_game_audio(env))
		return (false);
	SDL_SetRelativeMouseMode(true);
	return (true);
}

bool		edit_pause_menu(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	env->gui.pause_menu.container->component.is_visible = false;
	env->main_window->main_container->component.need_redraw = true;
	env->gui.status = GUI_NONE;
	env->time_scale = 1.f;
	env->app_state = APP_EDITOR;
	free_remaining_objects(env);
	destroy_object_manager(env);
	free_levels_manager_3d(env);
	return (true);
}

bool		settings_pause_menu(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	init_settings_menu(env);
	return (true);
}

bool		quit_pause_menu(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	env->time_scale = 1.f;
	free_remaining_objects(env);
	destroy_object_manager(env);
	free_levels_manager_3d(env);
	load_scene(env->scenes.main_menu);
	return (true);
}
