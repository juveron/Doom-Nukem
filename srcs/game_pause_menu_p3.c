/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_pause_menu_p3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:46:11 by thboura           #+#    #+#             */
/*   Updated: 2020/06/27 16:48:40 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pause_menu_internal.h"

bool	create_exit_button(t_env *env, t_game_pause *menu,
	t_pause_menu_handler *handler)
{
	if (!(menu->exit_button = create_button(
		(SDL_Rect){handler->box.w / 2 - handler->button.x / 2,
			4 * (handler->box.h / handler->num_of_buttons) + (handler->box.h
			/ (handler->num_of_buttons * 2)) - (handler->button.y / 2),
			handler->button.x, handler->button.y},
		0X777777FF, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_game_pause(menu));
	if (!button_change_name(menu->exit_button, "EXIT"))
		return (destroy_game_pause(menu));
	if (!add_default_action(menu->exit_button->on_click,
		&(t_default_event){exit_game_pause, env}))
		return (destroy_game_pause(menu));
	if (!add_default_action(menu->exit_button->on_enter,
		&(t_default_event){on_enter_pause_menu, menu->exit_button}))
		return (destroy_game_pause(menu));
	if (!add_default_action(menu->exit_button->on_leave,
		&(t_default_event){on_leave_pause_menu, menu->exit_button}))
		return (destroy_game_pause(menu));
	if (!container_add(menu->container, menu->exit_button))
		return (destroy_game_pause(menu));
	return (true);
}
