/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu_p2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 21:39:06 by thboura           #+#    #+#             */
/*   Updated: 2020/06/06 15:38:23 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pause_menu_internal.h"

static bool	create_resume_button(t_env *env, t_pause_menu *menu,
	t_pause_menu_handler *handler)
{
	if (!(menu->resume_button = create_button(
		(SDL_Rect){handler->box.w / 2 - handler->button.x / 2,
			0 * (handler->box.h / handler->num_of_buttons) + (handler->box.h
			/ (handler->num_of_buttons * 2)) - (handler->button.y / 2),
			handler->button.x, handler->button.y},
		0X777777FF, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_pause_menu(menu));
	if (!button_change_name(menu->resume_button, "RESUME"))
		return (destroy_pause_menu(menu));
	if (!add_default_action(menu->resume_button->on_click,
		&(t_default_event){resume_pause_menu, env}))
		return (destroy_pause_menu(menu));
	if (!add_default_action(menu->resume_button->on_enter,
		&(t_default_event){on_enter_pause_menu, menu->resume_button}))
		return (destroy_pause_menu(menu));
	if (!add_default_action(menu->resume_button->on_leave,
		&(t_default_event){on_leave_pause_menu, menu->resume_button}))
		return (destroy_pause_menu(menu));
	if (!container_add(menu->container, menu->resume_button))
		return (destroy_pause_menu(menu));
	return (true);
}

static bool	create_edit_button(t_env *env, t_pause_menu *menu,
	t_pause_menu_handler *handler)
{
	if (!(menu->edit_button = create_button(
		(SDL_Rect){handler->box.w / 2 - handler->button.x / 2,
			1 * (handler->box.h / handler->num_of_buttons) + (handler->box.h
			/ (handler->num_of_buttons * 2)) - (handler->button.y / 2),
			handler->button.x, handler->button.y},
		0X777777FF, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_pause_menu(menu));
	if (!button_change_name(menu->edit_button, "EDIT"))
		return (destroy_pause_menu(menu));
	if (!add_default_action(menu->edit_button->on_click,
		&(t_default_event){edit_pause_menu, env}))
		return (destroy_pause_menu(menu));
	if (!add_default_action(menu->edit_button->on_enter,
		&(t_default_event){on_enter_pause_menu, menu->edit_button}))
		return (destroy_pause_menu(menu));
	if (!add_default_action(menu->edit_button->on_leave,
		&(t_default_event){on_leave_pause_menu, menu->edit_button}))
		return (destroy_pause_menu(menu));
	if (!container_add(menu->container, menu->edit_button))
		return (destroy_pause_menu(menu));
	return (true);
}

static bool	create_settings_button(t_env *env, t_pause_menu *menu,
	t_pause_menu_handler *handler)
{
	if (!(menu->settings_button = create_button(
		(SDL_Rect){handler->box.w / 2 - handler->button.x / 2,
			2 * (handler->box.h / handler->num_of_buttons) + (handler->box.h
			/ (handler->num_of_buttons * 2)) - (handler->button.y / 2),
			handler->button.x, handler->button.y},
		0X777777FF, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_pause_menu(menu));
	if (!button_change_name(menu->settings_button, "SETTINGS"))
		return (destroy_pause_menu(menu));
	if (!add_default_action(menu->settings_button->on_click,
		&(t_default_event){settings_pause_menu, env}))
		return (destroy_pause_menu(menu));
	if (!add_default_action(menu->settings_button->on_enter,
		&(t_default_event){on_enter_pause_menu, menu->settings_button}))
		return (destroy_pause_menu(menu));
	if (!add_default_action(menu->settings_button->on_leave,
		&(t_default_event){on_leave_pause_menu, menu->settings_button}))
		return (destroy_pause_menu(menu));
	if (!container_add(menu->container, menu->settings_button))
		return (destroy_pause_menu(menu));
	return (true);
}

static bool	create_quit_button(t_env *env, t_pause_menu *menu,
	t_pause_menu_handler *handler)
{
	if (!(menu->quit_button = create_button(
		(SDL_Rect){handler->box.w / 2 - handler->button.x / 2,
			3 * (handler->box.h / handler->num_of_buttons) + (handler->box.h
			/ (handler->num_of_buttons * 2)) - (handler->button.y / 2),
			handler->button.x, handler->button.y},
		0X777777FF, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_pause_menu(menu));
	if (!button_change_name(menu->quit_button, "QUIT"))
		return (destroy_pause_menu(menu));
	if (!add_default_action(menu->quit_button->on_click,
		&(t_default_event){quit_pause_menu, env}))
		return (destroy_pause_menu(menu));
	if (!add_default_action(menu->quit_button->on_enter,
		&(t_default_event){on_enter_pause_menu, menu->quit_button}))
		return (destroy_pause_menu(menu));
	if (!add_default_action(menu->quit_button->on_leave,
		&(t_default_event){on_leave_pause_menu, menu->quit_button}))
		return (destroy_pause_menu(menu));
	if (!container_add(menu->container, menu->quit_button))
		return (destroy_pause_menu(menu));
	return (true);
}

bool		create_pause_menu(t_env *env, t_pause_menu *menu)
{
	t_pause_menu_handler	handler;

	handler.num_of_buttons = 4;
	handler.box.w = WIDTH / 3;
	handler.box.h = HEIGHT / 2;
	handler.box.x = WIDTH / 3;
	handler.box.y = HEIGHT / 4;
	handler.button.x = handler.box.w / 2;
	handler.button.y = handler.box.h / (handler.num_of_buttons + 1);
	if (!(menu->container = create_container(handler.box, false, 0)))
		return (false);
	if (!create_resume_button(env, menu, &handler)
		|| !create_edit_button(env, menu, &handler)
		|| !create_settings_button(env, menu, &handler)
		|| !create_quit_button(env, menu, &handler))
		return (false);
	if (!container_add(env->main_window->main_container, menu->container))
		return (destroy_pause_menu(menu));
	menu->container->component.is_visible = false;
	return (true);
}
