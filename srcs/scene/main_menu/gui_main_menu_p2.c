/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main_menu_p2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:59:06 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/12 11:33:51 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "gui_main_menu_internal.h"

bool	on_clic_settings(void *param)
{
	t_env	*env;

	env = param;
	init_settings_menu(env);
	env->gui.main_menu.container->component.is_visible = false;
	return (true);
}

bool	create_settings_button(t_main_menu *main_menu, t_env *env)
{
	if (!(main_menu->settings_button = create_button((SDL_Rect){10, 202, 780,
			90}, 0x77777700, env->fonts.deja_vu_sans_momo_60))
		|| !button_change_name(main_menu->settings_button, "Settings")
		|| !add_default_action(main_menu->settings_button->on_enter,
			&(t_default_event){on_enter, main_menu->settings_button})
		|| !add_default_action(main_menu->settings_button->on_leave,
			&(t_default_event){on_leave, main_menu->settings_button})
		|| !add_default_action(main_menu->settings_button->on_click,
			&(t_default_event){on_clic_settings, env})
		|| !container_add(main_menu->container, main_menu->settings_button))
		return (false);
	component_add_background_image(main_menu->settings_button,
		env->gui_image.button_background_1);
	main_menu->settings_button->component.use_background = false;
	return (true);
}

bool	on_clic_quit(void *param)
{
	(void)param;
	get_context()->run = false;
	return (true);
}

bool	create_quit_button(t_main_menu *main_menu, t_env *env)
{
	if (!(main_menu->quit_button = create_button((SDL_Rect){10, 300, 780,
			90}, 0x77777700, env->fonts.deja_vu_sans_momo_60))
		|| !button_change_name(main_menu->quit_button, "Quit")
		|| !add_default_action(main_menu->quit_button->on_enter,
			&(t_default_event){on_enter, main_menu->quit_button})
		|| !add_default_action(main_menu->quit_button->on_leave,
			&(t_default_event){on_leave, main_menu->quit_button})
		|| !add_default_action(main_menu->quit_button->on_click,
			&(t_default_event){on_clic_quit, env})
		|| !container_add(main_menu->container, main_menu->quit_button))
		return (false);
	component_add_background_image(main_menu->quit_button,
		env->gui_image.button_background_1);
	main_menu->quit_button->component.use_background = false;
	return (true);
}

bool	destroy_gui_main_menu(t_main_menu *main_menu)
{
	int	ret;

	ret = 0;
	ret += !destroy_button(&main_menu->play_button);
	ret += !destroy_button(&main_menu->editor_button);
	ret += !destroy_button(&main_menu->settings_button);
	ret += !destroy_button(&main_menu->quit_button);
	ret += !destroy_container(&main_menu->container);
	return (ret == 0);
}
