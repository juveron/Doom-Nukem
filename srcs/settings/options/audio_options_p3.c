/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_options_p3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:33:14 by thboura           #+#    #+#             */
/*   Updated: 2020/07/12 02:56:03 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		destroy_gui_options(t_gui_options *gui)
{
	int	ret;

	ret = 0;
	if (!gui)
		return (true);
	ret += !destroy_fslider(&gui->select_button_amplitude_fslider);
	ret += !destroy_label(&gui->select_button_amplitude_label);
	ret += !destroy_fslider(&gui->close_pause_amplitude_fslider);
	ret += !destroy_label(&gui->close_pause_amplitude_label);
	ret += !destroy_fslider(&gui->open_pause_amplitude_fslider);
	ret += !destroy_label(&gui->open_pause_amplitude_label);
	ret += !destroy_fslider(&gui->gui_amplitude_fslider);
	ret += !destroy_label(&gui->gui_amplitude_label);
	return (ret == 0);
}

static bool	create_gui_options_p4(t_env *env, t_gui_options *gui,
	SDL_Rect box, size_t num_of_buttons)
{
	if (!(gui->select_button_amplitude_label = create_label(vec2i(75,
			7 * (box.h / num_of_buttons) + (box.h / num_of_buttons / 2
			- (int)(19 / 2)) + (box.h % num_of_buttons)), 0xFFFFFFFF,
			env->fonts.deja_vu_sans_momo_16, 0x666666FF))
		|| !label_change_name(gui->select_button_amplitude_label,
			"Select_button")
		|| !container_add(env->gui.settings_menu.audio.container,
			gui->select_button_amplitude_label)
		|| !(gui->select_button_amplitude_fslider = create_fslider(
			(SDL_Rect){box.w / 2, 7 * (box.h / num_of_buttons) + box.h
			/ num_of_buttons / 4 + (box.h % num_of_buttons),
			box.w / 2 - 25, box.h / num_of_buttons / 2}, 0.f, 1.f))
		|| !add_custom_action(gui->select_button_amplitude_fslider->
			on_value_change,
			&(t_custom_event){&slider_update_select_button_amplitude,
			&env->sound_manager}))
		return (destroy_gui_options(gui));
	fslider_set_percent_value(gui->select_button_amplitude_fslider,
		env->sound_manager.audio_gui.select_button.amplitude);
	if (!container_add(env->gui.settings_menu.audio.container,
		gui->select_button_amplitude_fslider))
		return (destroy_gui_options(gui));
	return (true);
}

static bool	create_gui_options_p3(t_env *env, t_gui_options *gui,
	SDL_Rect box, size_t num_of_buttons)
{
	if (!(gui->close_pause_amplitude_label = create_label(vec2i(75,
			6 * (box.h / num_of_buttons) + (box.h / num_of_buttons / 2
			- (int)(19 / 2)) + (box.h % num_of_buttons)), 0xFFFFFFFF,
			env->fonts.deja_vu_sans_momo_16, 0x666666FF))
		|| !label_change_name(gui->close_pause_amplitude_label, "Close_pause")
		|| !container_add(env->gui.settings_menu.audio.container,
			gui->close_pause_amplitude_label)
		|| !(gui->close_pause_amplitude_fslider = create_fslider(
			(SDL_Rect){box.w / 2, 6 * (box.h / num_of_buttons) + box.h
			/ num_of_buttons / 4 + (box.h % num_of_buttons),
			box.w / 2 - 25, box.h / num_of_buttons / 2}, 0.f, 1.f))
		|| !add_custom_action(gui->close_pause_amplitude_fslider->
			on_value_change,
			&(t_custom_event){&slider_update_close_pause_amplitude,
			&env->sound_manager}))
		return (destroy_gui_options(gui));
	fslider_set_percent_value(gui->close_pause_amplitude_fslider,
		env->sound_manager.audio_gui.close_pause_menu.amplitude);
	if (!container_add(env->gui.settings_menu.audio.container,
		gui->close_pause_amplitude_fslider))
		return (destroy_gui_options(gui));
	return (create_gui_options_p4(env, gui, box,
		num_of_buttons));
}

static bool	create_gui_options_p2(t_env *env, t_gui_options *gui,
	SDL_Rect box, size_t num_of_buttons)
{
	if (!(gui->open_pause_amplitude_label = create_label(vec2i(75,
			5 * (box.h / num_of_buttons) + (box.h / num_of_buttons / 2
			- (int)(19 / 2)) + (box.h % num_of_buttons)), 0xFFFFFFFF,
			env->fonts.deja_vu_sans_momo_16, 0x666666FF))
		|| !label_change_name(gui->open_pause_amplitude_label, "Open_pause")
		|| !container_add(env->gui.settings_menu.audio.container,
			gui->open_pause_amplitude_label)
		|| !(gui->open_pause_amplitude_fslider = create_fslider(
			(SDL_Rect){box.w / 2, 5 * (box.h / num_of_buttons) + box.h
			/ num_of_buttons / 4 + (box.h % num_of_buttons),
			box.w / 2 - 25, box.h / num_of_buttons / 2}, 0.f, 1.f))
		|| !add_custom_action(gui->open_pause_amplitude_fslider->
			on_value_change,
			&(t_custom_event){&slider_update_open_pause_amplitude,
			&env->sound_manager}))
		return (destroy_gui_options(gui));
	fslider_set_percent_value(gui->open_pause_amplitude_fslider,
		env->sound_manager.audio_gui.open_pause_menu.amplitude);
	if (!container_add(env->gui.settings_menu.audio.container,
		gui->open_pause_amplitude_fslider))
		return (destroy_gui_options(gui));
	return (create_gui_options_p3(env, gui, box,
		num_of_buttons));
}

bool		create_gui_options(t_env *env, t_gui_options *gui, SDL_Rect box,
	size_t num_of_buttons)
{
	if (!(gui->gui_amplitude_label = create_label(vec2i(50,
			4 * (box.h / num_of_buttons) + (box.h / num_of_buttons / 2
			- (int)(19 / 2)) + (box.h % num_of_buttons)), 0xFFFFFFFF,
			env->fonts.deja_vu_sans_momo_16, 0x666666FF))
		|| !label_change_name(gui->gui_amplitude_label, "Gui")
		|| !container_add(env->gui.settings_menu.audio.container,
			gui->gui_amplitude_label)
		|| !(gui->gui_amplitude_fslider = create_fslider(
			(SDL_Rect){box.w / 2, 4 * (box.h / num_of_buttons) + box.h
			/ num_of_buttons / 4 + (box.h % num_of_buttons),
			box.w / 2 - 25, box.h / num_of_buttons / 2}, 0.f, 1.f))
		|| !add_custom_action(gui->gui_amplitude_fslider->on_value_change,
			&(t_custom_event){&slider_update_gui_amplitude,
			&env->sound_manager}))
		return (destroy_gui_options(gui));
	fslider_set_percent_value(gui->gui_amplitude_fslider,
		env->sound_manager.audio_gui.amplitude);
	if (!container_add(env->gui.settings_menu.audio.container,
		gui->gui_amplitude_fslider))
		return (destroy_gui_options(gui));
	return (create_gui_options_p2(env, gui, box, num_of_buttons));
}
