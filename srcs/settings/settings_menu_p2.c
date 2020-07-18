/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu_p2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:38:38 by thboura           #+#    #+#             */
/*   Updated: 2020/06/12 16:44:35 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	create_settings_menu_p4(t_env *env, t_settings_menu *menu)
{
	if (!create_controls_options(env, &menu->controls))
		return (destroy_settings_menu(menu));
	if (!(menu->controls_button = create_button((SDL_Rect){
		2 * ((env->main_window->size.x - 100) / NUM_OF_OPTIONS) + 50, 0,
		(env->main_window->size.x - 100) / NUM_OF_OPTIONS, 50},
		0X666666FF, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_settings_menu(menu));
	if (!button_change_name(menu->controls_button, "Controls"))
		return (destroy_settings_menu(menu));
	if (!add_default_action(menu->controls_button->on_click,
		&(t_default_event){init_controls_options, env}))
		return (destroy_settings_menu(menu));
	if (!container_add(menu->container, menu->controls_button))
		return (destroy_settings_menu(menu));
	if (!container_add(env->main_window->main_container, menu->container))
		return (destroy_settings_menu(menu));
	menu->container->component.is_visible = false;
	return (true);
}

static bool	create_settings_menu_p3(t_env *env, t_settings_menu *menu)
{
	if (!create_other_options(env, &menu->other))
		return (destroy_settings_menu(menu));
	if (!(menu->other_button = create_button((SDL_Rect){
		1 * ((env->main_window->size.x - 100) / NUM_OF_OPTIONS) + 50, 0,
		(env->main_window->size.x - 100) / NUM_OF_OPTIONS, 50},
		0X666666FF, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_settings_menu(menu));
	if (!button_change_name(menu->other_button, "Other"))
		return (destroy_settings_menu(menu));
	if (!add_default_action(menu->other_button->on_click,
		&(t_default_event){init_other_options, env}))
		return (destroy_settings_menu(menu));
	if (!container_add(menu->container, menu->other_button))
		return (destroy_settings_menu(menu));
	return (create_settings_menu_p4(env, menu));
}

bool		create_settings_menu_p2(t_env *env, t_settings_menu *menu)
{
	if (!create_audio_options(env, &menu->audio))
		return (destroy_settings_menu(menu));
	if (!(menu->audio_button = create_button((SDL_Rect){
		0 * ((env->main_window->size.x - 100) / NUM_OF_OPTIONS) + 50, 0,
		(env->main_window->size.x - 100) / NUM_OF_OPTIONS, 50},
		0X666666FF, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_settings_menu(menu));
	if (!button_change_name(menu->audio_button, "Audio"))
		return (destroy_settings_menu(menu));
	if (!add_default_action(menu->audio_button->on_click,
		&(t_default_event){init_audio_options, env}))
		return (destroy_settings_menu(menu));
	if (!container_add(menu->container, menu->audio_button))
		return (destroy_settings_menu(menu));
	return (create_settings_menu_p3(env, menu));
}
