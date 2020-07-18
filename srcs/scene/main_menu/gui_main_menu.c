/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:59:06 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/10 11:52:06 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "gui_main_menu_internal.h"

bool	on_clic_game(void *param)
{
	t_env *env;

	env = param;
	if (!check_valid_map(env))
		return (true);
	load_scene(env->scenes.game);
	return (true);
}

bool	create_play_button(t_main_menu *main_menu, t_env *env)
{
	if (!(main_menu->play_button = create_button((SDL_Rect){10, 10, 780,
			90}, 0x77777700, env->fonts.deja_vu_sans_momo_60))
		|| !button_change_name(main_menu->play_button, "Play")
		|| !add_default_action(main_menu->play_button->on_enter,
			&(t_default_event){on_enter, main_menu->play_button})
		|| !add_default_action(main_menu->play_button->on_leave,
			&(t_default_event){on_leave, main_menu->play_button})
		|| !add_default_action(main_menu->play_button->on_click,
			&(t_default_event){on_clic_game, env})
		|| !container_add(main_menu->container, main_menu->play_button))
		return (false);
	component_add_background_image(main_menu->play_button,
		env->gui_image.button_background_1);
	main_menu->play_button->component.use_background = false;
	return (true);
}

bool	on_clic_editor(void *param)
{
	t_env *env;

	env = param;
	load_scene(env->scenes.editor);
	return (true);
}

bool	create_editor_button(t_main_menu *main_menu, t_env *env)
{
	if (!(main_menu->editor_button = create_button((SDL_Rect){10, 106, 780,
			90}, 0x77777700, env->fonts.deja_vu_sans_momo_60))
		|| !button_change_name(main_menu->editor_button, "Editor")
		|| !add_default_action(main_menu->editor_button->on_enter,
			&(t_default_event){on_enter, main_menu->editor_button})
		|| !add_default_action(main_menu->editor_button->on_leave,
			&(t_default_event){on_leave, main_menu->editor_button})
		|| !add_default_action(main_menu->editor_button->on_click,
			&(t_default_event){on_clic_editor, env})
		|| !container_add(main_menu->container, main_menu->editor_button))
		return (false);
	component_add_background_image(main_menu->editor_button,
		env->gui_image.button_background_1);
	main_menu->editor_button->component.use_background = false;
	return (true);
}

bool	create_gui_main_menu(t_main_menu *main_menu, t_env *env)
{
	if (!(main_menu->container = create_container(
			(SDL_Rect){400, 200, 800, 400}, false, 0x333333FF))
		|| !create_play_button(main_menu, env)
		|| !create_editor_button(main_menu, env)
		|| !create_settings_button(main_menu, env)
		|| !create_quit_button(main_menu, env)
		|| !container_add(env->main_window->main_container,
			main_menu->container))
	{
		destroy_gui_main_menu(main_menu);
		return (false);
	}
	return (true);
}
