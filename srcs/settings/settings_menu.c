/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 16:34:16 by thboura           #+#    #+#             */
/*   Updated: 2020/06/26 13:51:42 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	destroy_settings_menu(t_settings_menu *menu)
{
	int	ret;

	ret = 0;
	if (!menu)
		return (false);
	ret += !destroy_audio_options(&menu->audio);
	ret += !destroy_other_options(&menu->other);
	ret += !destroy_controls_options(&menu->controls);
	ret += !destroy_button(&menu->resume_button);
	ret += !destroy_button(&menu->exit_button);
	ret += !destroy_button(&menu->audio_button);
	ret += !destroy_button(&menu->other_button);
	ret += !destroy_button(&menu->controls_button);
	ret += !destroy_container(&menu->container);
	return (ret == 0);
}

void	disable_current_option(t_settings_menu *menu)
{
	if (menu->current_option == AUDIO_OPTION)
	{
		menu->audio_button->component.background = 0X666666FF;
		menu->audio_button->component.need_redraw = true;
		menu->audio.container->component.is_visible = false;
	}
	else if (menu->current_option == OTHER_OPTION)
	{
		menu->other_button->component.background = 0X666666FF;
		menu->other_button->component.need_redraw = true;
		menu->other.container->component.is_visible = false;
	}
	else if (menu->current_option == CONTROLS_OPTION)
	{
		menu->controls_button->component.background = 0X666666FF;
		menu->controls_button->component.need_redraw = true;
		menu->controls.container->component.is_visible = false;
	}
	menu->container->component.need_redraw = true;
}

bool	create_settings_menu(t_env *env, t_settings_menu *menu)
{
	if (!(menu->container = create_container((SDL_Rect){0, 0,
		env->main_window->size.x, env->main_window->size.y}, false, 0)))
		return (false);
	if (!(menu->resume_button = create_button((SDL_Rect){0, 0, 50, 50},
		0XFF0000FF, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_settings_menu(menu));
	if (!button_change_name(menu->resume_button, "<"))
		return (destroy_settings_menu(menu));
	if (!add_default_action(menu->resume_button->on_click,
		&(t_default_event){resume_settings_menu, env}))
		return (destroy_settings_menu(menu));
	if (!container_add(menu->container, menu->resume_button))
		return (destroy_settings_menu(menu));
	if (!(menu->exit_button = create_button((SDL_Rect){env->main_window->size.x
		- 50, 0, 50, 50}, 0XFF0000FF, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_settings_menu(menu));
	if (!button_change_name(menu->exit_button, "X"))
		return (destroy_settings_menu(menu));
	if (!add_default_action(menu->exit_button->on_click,
		&(t_default_event){exit_settings_menu, env}))
		return (destroy_settings_menu(menu));
	if (!container_add(menu->container, menu->exit_button))
		return (destroy_settings_menu(menu));
	return (create_settings_menu_p2(env, menu));
}

void	init_settings_menu(t_env *env)
{
	if (env->gui.status != GUI_SETTINGS)
	{
		if (env->gui.status != GUI_MAIN_MENU)
		{
			env->gui.window->component.is_visible = false;
			env->gui.pause_menu.container->component.is_visible = false;
			env->gui.game_pause_menu.container->component.is_visible = false;
		}
		env->gui.settings_menu.container->component.is_visible = true;
		env->gui.settings_menu.current_option = NUM_OF_OPTIONS;
		init_audio_options(env);
		env->main_window->main_container->component.need_redraw = true;
		env->gui.settings_menu.prev_app_state = env->app_state;
		env->app_state = APP_SETTINGS;
		env->gui.settings_menu.prev_gui_status = env->gui.status;
	}
	env->gui.status = GUI_SETTINGS;
}
