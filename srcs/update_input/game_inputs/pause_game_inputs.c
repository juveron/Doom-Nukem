/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_game_inputs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:04:07 by thboura           #+#    #+#             */
/*   Updated: 2020/06/27 19:46:19 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

static int	activate_game_pause_menu(t_env *env)
{
	init_game_pause(env);
	if (!change_all_sources_state(&env->sound_manager, SRC_PAUSE))
		return (-1);
	if (!change_source_state(env->sound_manager.audio_gui.
		close_pause_menu.source, SRC_STOP))
		return (-1);
	if (!change_source_state(env->sound_manager.audio_gui.
		open_pause_menu.source, SRC_PLAY))
		return (-1);
	clock_pause(&env->hud.time);
	SDL_SetRelativeMouseMode(false);
	env->time_scale = 0;
	return (true);
}

static void	select_option(t_env *env, t_game_pause *menu, bool up)
{
	int			tmp;
	int			current;
	int			ret;
	int			num_of_buttons;

	num_of_buttons = 5;
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

static bool	validate_game_pause_button(t_game_pause *menu)
{
	if (menu->is_over_button == 1)
		return (trigger_gui_default_event(menu->resume_button->on_click));
	if (menu->is_over_button == 2)
		return (trigger_gui_default_event(menu->restart_button->on_click));
	if (menu->is_over_button == 3)
		return (trigger_gui_default_event(menu->settings_button->on_click));
	if (menu->is_over_button == 4)
		return (trigger_gui_default_event(menu->quit_button->on_click));
	if (menu->is_over_button == 5)
		return (trigger_gui_default_event(menu->exit_button->on_click));
	return (true);
}

int			pause_game_inputs(t_env *env)
{
	if (env->gui.status != GUI_PAUSE && get_key_down(env->shortcuts.game.pause))
		return (activate_game_pause_menu(env));
	else if (env->gui.status != GUI_PAUSE)
		return (false);
	if (get_key_down(env->shortcuts.menu.up))
		select_option(env, &env->gui.game_pause_menu, true);
	else if (get_key_down(env->shortcuts.menu.down))
		select_option(env, &env->gui.game_pause_menu, false);
	else if (get_key_down(env->shortcuts.menu.validate))
	{
		if (!validate_game_pause_button(&env->gui.game_pause_menu))
			return (-1);
	}
	else if (get_key_down(env->shortcuts.menu.quit))
	{
		if (!trigger_gui_default_event(env->gui.game_pause_menu.quit_button->
			on_click))
			return (-1);
	}
	return (true);
}
