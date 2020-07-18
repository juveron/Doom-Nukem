/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_pause_menu_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 15:12:35 by thboura           #+#    #+#             */
/*   Updated: 2020/06/27 17:41:08 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		resume_game_pause(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	env->gui.game_pause_menu.container->component.is_visible = false;
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
	clock_unpause(&env->hud.time);
	SDL_SetRelativeMouseMode(true);
	return (true);
}

bool		restart_game_pause(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	env->gui.game_pause_menu.container->component.is_visible = false;
	env->main_window->main_container->component.need_redraw = true;
	env->gui.status = GUI_NONE;
	env->time_scale = 1.f;
	if (!change_all_sources_state(&env->sound_manager, SRC_STOP))
		return (false);
	return (set_game_start(env));
}

bool		quit_game_pause(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	env->time_scale = 1.f;
	load_scene(env->scenes.main_menu);
	return (true);
}

bool		exit_game_pause(void *param)
{
	(void)param;
	get_context()->run = false;
	return (true);
}
