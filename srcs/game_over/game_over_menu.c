/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 15:02:12 by thboura           #+#    #+#             */
/*   Updated: 2020/06/25 17:43:14 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_over_internal.h"

bool		destroy_game_over_menu(t_game_over_menu *menu)
{
	int ret;

	ret = 0;
	ret += !destroy_button(&menu->exit_button);
	ret += !destroy_button(&menu->main_menu_button);
	ret += !destroy_button(&menu->restart_button);
	ret += !destroy_label(&menu->game_over_label);
	ret += !destroy_container(&menu->container);
	return (ret == 0);
}

static bool	create_game_over_menu_p2(t_env *env, t_game_over_menu *menu)
{
	if (!(menu->main_menu_button = create_button((SDL_Rect){750, 700, 100, 50},
			0XFF0000FF, env->fonts.deja_vu_sans_momo_16))
		|| !button_change_name(menu->main_menu_button, "Main menu")
		|| !add_default_action(menu->main_menu_button->on_click,
			&(t_default_event){main_menu_game_over_menu, env})
		|| !container_add(menu->container, menu->main_menu_button)
		|| !(menu->exit_button = create_button((SDL_Rect){950, 700, 100, 50},
			0XFF0000FF, env->fonts.deja_vu_sans_momo_16))
		|| !button_change_name(menu->exit_button, "Exit")
		|| !add_default_action(menu->exit_button->on_click,
			&(t_default_event){exit_game_over_menu, env})
		|| !container_add(menu->container, menu->exit_button)
		|| !container_add(env->main_window->main_container, menu->container))
		return (destroy_game_over_menu(menu) && 0);
	menu->game_over_label->component.rect.x = env->main_window->size.x / 2
		- menu->game_over_label->component.rect.w / 2;
	menu->game_over_label->component.rect.y = env->main_window->size.y / 2
		- menu->game_over_label->component.rect.h / 2;
	menu->container->component.is_visible = false;
	return (true);
}

bool		create_game_over_menu(t_env *env, t_game_over_menu *menu)
{
	if (!(menu->container = create_container((SDL_Rect){0, 0,
		env->main_window->size.x, env->main_window->size.y}, true, 0xFF)))
		return (false);
	if (!(menu->game_over_label = create_label(vec2i(0, 0), 0xFF0000FF,
			env->fonts.covid_virus_120, 0x000000FF))
		|| !label_change_name(menu->game_over_label, "GAME OVER")
		|| !container_add(menu->container, menu->game_over_label))
		return (destroy_game_over_menu(menu) && 0);
	if (!(menu->restart_button = create_button((SDL_Rect){550, 700, 100, 50},
			0XFF0000FF, env->fonts.deja_vu_sans_momo_16))
		|| !button_change_name(menu->restart_button, "Restart")
		|| !add_default_action(menu->restart_button->on_click,
			&(t_default_event){resume_game_over_menu, env})
		|| !container_add(menu->container, menu->restart_button))
		return (destroy_game_over_menu(menu) && 0);
	return (create_game_over_menu_p2(env, menu));
}

void		init_game_over_gui_menu(t_env *env)
{
	if (env->gui.status != GUI_GAME_OVER)
	{
		env->gui.game_over_menu.container->component.is_visible = true;
		env->main_window->main_container->component.need_redraw = true;
	}
	env->gui.status = GUI_GAME_OVER;
}
