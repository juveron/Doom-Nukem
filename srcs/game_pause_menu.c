/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_pause_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 14:50:17 by thboura           #+#    #+#             */
/*   Updated: 2020/06/27 16:43:49 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pause_menu_internal.h"

static bool	update_game_pause_p2(t_env *env, t_game_pause *menu)
{
	if (menu->quit_button->is_over && menu->is_over_button != 4)
	{
		menu->is_over_button = 4;
		return (change_source_state(env->sound_manager.audio_gui.select_button.
			source, SRC_PLAY));
	}
	else if (menu->exit_button->is_over && menu->is_over_button != 5)
	{
		menu->is_over_button = 5;
		return (change_source_state(env->sound_manager.audio_gui.select_button.
			source, SRC_PLAY));
	}
	else if (!menu->resume_button->is_over && !menu->restart_button->is_over
		&& !menu->settings_button->is_over && !menu->quit_button->is_over
		&& !menu->exit_button->is_over)
		menu->is_over_button = 0;
	return (true);
}

bool		update_game_pause(t_env *env, t_game_pause *menu)
{
	if (env->gui.status != GUI_PAUSE)
		return (true);
	if (menu->resume_button->is_over && menu->is_over_button != 1)
	{
		menu->is_over_button = 1;
		return (change_source_state(env->sound_manager.audio_gui.select_button.
			source, SRC_PLAY));
	}
	else if (menu->restart_button->is_over && menu->is_over_button != 2)
	{
		menu->is_over_button = 2;
		return (change_source_state(env->sound_manager.audio_gui.select_button.
			source, SRC_PLAY));
	}
	else if (menu->settings_button->is_over && menu->is_over_button != 3)
	{
		menu->is_over_button = 3;
		return (change_source_state(env->sound_manager.audio_gui.select_button.
			source, SRC_PLAY));
	}
	else
		return (update_game_pause_p2(env, menu));
}

bool		destroy_game_pause(t_game_pause *menu)
{
	int	ret;

	ret = 0;
	ret += !destroy_button(&menu->resume_button);
	ret += !destroy_button(&menu->restart_button);
	ret += !destroy_button(&menu->settings_button);
	ret += !destroy_button(&menu->quit_button);
	ret += !destroy_button(&menu->exit_button);
	ret += !destroy_container(&menu->container);
	return (ret == 0);
}

void		init_game_pause(t_env *env)
{
	if (env->gui.status != GUI_PAUSE)
	{
		env->gui.window->component.is_visible = false;
		env->gui.texture_menu->window->component.is_visible = false;
		env->gui.game_pause_menu.container->component.is_visible = true;
		env->main_window->main_container->component.need_redraw = true;
		env->gui.game_pause_menu.is_over_button = 0;
	}
	env->gui.status = GUI_PAUSE;
}
