/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:30:54 by thboura           #+#    #+#             */
/*   Updated: 2020/07/15 03:03:21 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "win_internal.h"

bool		destroy_win_menu(t_win_menu *menu)
{
	int	ret;

	ret = 0;
	ret += !destroy_label(&menu->highscore_label);
	ret += !destroy_button(&menu->exit_button);
	ret += !destroy_button(&menu->main_menu_button);
	ret += !destroy_button(&menu->restart_button);
	ret += !destroy_label(&menu->win_label);
	ret += !destroy_label(&menu->time_label);
	ret += !destroy_container(&menu->container);
	return (ret == 0);
}

bool		init_win_gui_menu(t_env *env)
{
	char buffer[32];

	if (env->gui.status != GUI_WIN)
	{
		env->gui.win_menu.container->component.is_visible = true;
		env->main_window->main_container->component.need_redraw = true;
		ft_snprintf(buffer, sizeof(buffer), "Your time: %02d:%02d:%02lu",
			(int)clock_get_seconds(&env->hud.time) / 60 % 60,
			(int)clock_get_seconds(&env->hud.time) % 60,
			clock_get_milliseconds(&env->hud.time) % 1000 / 10);
		if (!label_change_name(env->gui.win_menu.time_label, buffer))
			return (false);
		env->gui.win_menu.time_label->component.rect.x = env->main_window->
			size.x / 2 - env->gui.win_menu.time_label->component.rect.w / 2;
		env->gui.win_menu.time_label->component.rect.y = env->main_window->
			size.y / 2 - 300;
		if (!set_highscore(env))
			return (false);
	}
	env->gui.status = GUI_WIN;
	return (true);
}

static bool	create_win_menu_p3(t_env *env, t_win_menu *menu)
{
	if (!(menu->time_label = create_label(vec2i(0, 0), 0xFFFFFFFF,
		env->fonts.deja_vu_sans_momo_30, 0x0))
		|| !container_add(menu->container, menu->time_label))
		return (destroy_win_menu(menu));
	if (!(menu->highscore_label = create_label(vec2i(0, 0), 0xFFFFFFFF,
		env->fonts.deja_vu_sans_momo_30, 0x0))
		|| !container_add(menu->container, menu->highscore_label))
		return (destroy_win_menu(menu));
	menu->win_label->component.rect.x = env->main_window->size.x / 2
		- menu->win_label->component.rect.w / 2;
	menu->win_label->component.rect.y = env->main_window->size.y / 2
		- menu->win_label->component.rect.h / 2;
	menu->container->component.is_visible = false;
	menu->animation = true;
	menu->animation_time = 1.f;
	menu->current_time = 0;
	return (true);
}

static bool	create_win_menu_p2(t_env *env, t_win_menu *menu)
{
	if (!(menu->main_menu_button = create_button((SDL_Rect){750, 700, 170, 50},
			0x77777700, env->fonts.deja_vu_sans_momo_30))
		|| !button_change_name(menu->main_menu_button, "Main menu")
		|| !add_default_action(menu->main_menu_button->on_click,
			&(t_default_event){main_menu_win_menu, env})
		|| !container_add(menu->container, menu->main_menu_button))
		return (destroy_win_menu(menu));
	if (!(menu->exit_button = create_button((SDL_Rect){950, 700, 150, 50},
			0x77777700, env->fonts.deja_vu_sans_momo_30))
		|| !button_change_name(menu->exit_button, "Exit")
		|| !add_default_action(menu->exit_button->on_click,
			&(t_default_event){exit_win_menu, env})
		|| !container_add(menu->container, menu->exit_button))
		return (destroy_win_menu(menu));
	if (!container_add(env->main_window->main_container, menu->container))
		return (destroy_win_menu(menu));
	if (!create_win_menu_p3(env, menu))
		return (destroy_win_menu(menu));
	return (true);
}

bool		create_win_menu(t_env *env, t_win_menu *menu)
{
	if (!(menu->container = create_container((SDL_Rect){0, 0,
			env->main_window->size.x, env->main_window->size.y}, false,
			0x0))
		|| !(menu->win_label = create_label(vec2i(0, 0), 0xFFFFFFFF,
				env->fonts.badabb_120, 0x0))
		|| !label_change_name(menu->win_label, "YOU WIN !!!")
		|| !container_add(menu->container, menu->win_label)
		|| !(menu->restart_button = create_button((SDL_Rect){550, 700, 150, 50},
				0x77777700, env->fonts.deja_vu_sans_momo_30))
		|| !button_change_name(menu->restart_button, "Restart")
		|| !add_default_action(menu->restart_button->on_click,
				&(t_default_event){resume_win_menu, env})
		|| !container_add(menu->container, menu->restart_button))
		return (destroy_win_menu(menu));
	return (create_win_menu_p2(env, menu));
}
