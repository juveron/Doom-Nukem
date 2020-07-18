/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 09:32:27 by thboura           #+#    #+#             */
/*   Updated: 2020/06/05 21:40:35 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	update_pause_menu_p2(t_env *env, t_pause_menu *menu)
{
	if (menu->quit_button->is_over && menu->is_over_button != 4)
	{
		menu->is_over_button = 4;
		return (change_source_state(env->sound_manager.audio_gui.select_button
			.source, SRC_PLAY));
	}
	else if (!menu->resume_button->is_over && !menu->edit_button->is_over
		&& !menu->settings_button->is_over && !menu->quit_button->is_over)
		menu->is_over_button = 0;
	return (true);
}

bool		update_pause_menu(t_env *env, t_pause_menu *menu)
{
	if (env->gui.status != GUI_PAUSE)
		return (true);
	if (menu->resume_button->is_over && menu->is_over_button != 1)
	{
		menu->is_over_button = 1;
		return (change_source_state(env->sound_manager.audio_gui.select_button.
			source, SRC_PLAY));
	}
	else if (menu->edit_button->is_over && menu->is_over_button != 2)
	{
		menu->is_over_button = 2;
		return (change_source_state(env->sound_manager.audio_gui.select_button.
			source, SRC_PLAY));
	}
	else if (menu->settings_button->is_over && menu->is_over_button != 3)
	{
		menu->is_over_button = 3;
		return (change_source_state(env->sound_manager.audio_gui.select_button
			.source, SRC_PLAY));
	}
	else
		return (update_pause_menu_p2(env, menu));
}

bool		destroy_pause_menu(t_pause_menu *menu)
{
	int	ret;

	ret = 0;
	ret += !destroy_button(&menu->resume_button);
	ret += !destroy_button(&menu->edit_button);
	ret += !destroy_button(&menu->settings_button);
	ret += !destroy_button(&menu->quit_button);
	ret += !destroy_container(&menu->container);
	return (ret == 0);
}

void		init_pause_menu(t_env *env)
{
	if (env->gui.status != GUI_PAUSE)
	{
		env->gui.window->component.is_visible = false;
		env->gui.texture_menu->window->component.is_visible = false;
		env->gui.pause_menu.container->component.is_visible = true;
		env->main_window->main_container->component.need_redraw = true;
		env->gui.pause_menu.is_over_button = 0;
	}
	env->gui.status = GUI_PAUSE;
}
