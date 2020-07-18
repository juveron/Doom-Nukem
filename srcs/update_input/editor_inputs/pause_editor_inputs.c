/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_editor_inputs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 15:32:58 by thboura           #+#    #+#             */
/*   Updated: 2020/06/24 16:43:12 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

static int	activate_editor_pause_menu(t_env *env)
{
	init_pause_menu(env);
	if (!change_all_sources_state(&env->sound_manager, SRC_PAUSE))
		return (-1);
	if (!change_source_state(env->sound_manager.audio_gui.
		close_pause_menu.source, SRC_STOP))
		return (-1);
	if (!change_source_state(env->sound_manager.audio_gui.
		open_pause_menu.source, SRC_PLAY))
		return (-1);
	SDL_SetRelativeMouseMode(false);
	env->time_scale = 0;
	return (true);
}

static void	select_option(t_env *env, t_pause_menu *menu, bool up)
{
	int			tmp;
	int			current;
	int			ret;
	int			num_of_buttons;

	num_of_buttons = 4;
	tmp = up ? -1 : 1;
	current = menu->is_over_button;
	if (current == 0)
		current = up ? 1 : num_of_buttons;
	ret = current + tmp;
	current = ret == 0 ? num_of_buttons : ret;
	if (current == num_of_buttons + 1)
		current = 1;
	SDL_WarpMouseInWindow(env->main_window->handle, WIDTH / 2,
		(current - 1) * (HEIGHT / 2 / num_of_buttons) + (HEIGHT / 2
		/ (num_of_buttons * 2)) + (HEIGHT / 4));
}

static bool	validate_pause_menu_button(t_pause_menu *menu)
{
	if (menu->is_over_button == 1)
		return (trigger_gui_default_event(menu->resume_button->on_click));
	if (menu->is_over_button == 2)
		return (trigger_gui_default_event(menu->edit_button->on_click));
	if (menu->is_over_button == 3)
		return (trigger_gui_default_event(menu->settings_button->on_click));
	if (menu->is_over_button == 4)
		return (trigger_gui_default_event(menu->quit_button->on_click));
	return (true);
}

int			pause_editor_inputs(t_env *env)
{
	if (env->gui.status != GUI_PAUSE && get_key_down(env->shortcuts.game.pause))
		return (activate_editor_pause_menu(env));
	else if (env->gui.status != GUI_PAUSE)
		return (false);
	if (get_key_down(env->shortcuts.menu.up))
		select_option(env, &env->gui.pause_menu, true);
	else if (get_key_down(env->shortcuts.menu.down))
		select_option(env, &env->gui.pause_menu, false);
	else if (get_key_down(env->shortcuts.menu.validate))
	{
		if (!validate_pause_menu_button(&env->gui.pause_menu))
			return (-1);
	}
	else if (get_key_down(env->shortcuts.menu.quit))
	{
		if (!trigger_gui_default_event(env->gui.pause_menu.quit_button->
			on_click))
			return (-1);
	}
	return (true);
}
