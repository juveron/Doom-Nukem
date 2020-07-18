/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:35:32 by thboura           #+#    #+#             */
/*   Updated: 2020/06/24 23:47:27 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		destroy_audio_options(t_audio_options *audio)
{
	int	ret;

	ret = 0;
	if (!audio)
		return (true);
	ret += !destroy_objects_options(&audio->objects);
	ret += !destroy_gui_options(&audio->gui);
	ret += !destroy_ambient_options(&audio->ambient);
	ret += !destroy_fslider(&audio->global_amplitude_fslider);
	ret += !destroy_label(&audio->global_amplitude_label);
	ret += !destroy_container(&audio->container);
	return (ret == 0);
}

static bool	create_audio_options_p2(t_env *env, t_audio_options *audio,
	SDL_Rect box, size_t num_of_buttons)
{
	if (!(audio->global_amplitude_label = create_label(vec2i(25,
			0 * (box.h / num_of_buttons) + (box.h / num_of_buttons / 2
			- (int)(19 / 2)) + (box.h % num_of_buttons)), 0xFFFFFFFF,
			env->fonts.deja_vu_sans_momo_16, 0x666666FF))
		|| !label_change_name(audio->global_amplitude_label,
			"Global volume")
		|| !container_add(env->gui.settings_menu.audio.container,
			audio->global_amplitude_label)
		|| !(audio->global_amplitude_fslider = create_fslider(
			(SDL_Rect){box.w / 2, 0 * (box.h / num_of_buttons) + box.h
			/ num_of_buttons / 4 + (box.h % num_of_buttons),
			box.w / 2 - 25, box.h / num_of_buttons / 2}, 0.f, 1.f))
		|| !add_custom_action(audio->global_amplitude_fslider->on_value_change,
			&(t_custom_event){&slider_update_global_amplitude,
			&env->sound_manager}))
		return (destroy_audio_options(audio) && 0);
	fslider_set_percent_value(audio->global_amplitude_fslider,
		env->sound_manager.global_amplitude);
	if (!container_add(env->gui.settings_menu.audio.container,
		audio->global_amplitude_fslider))
		return (destroy_audio_options(audio) && 0);
	return (true);
}

bool		create_audio_options(t_env *env, t_audio_options *audio)
{
	SDL_Rect	box;
	size_t		num_of_buttons;

	num_of_buttons = NUM_OF_SOURCES + 4;
	box.w = env->main_window->size.x;
	box.h = env->main_window->size.y - 50;
	box.x = 0;
	box.y = 50;
	if (!(audio->container = create_container(box, true, 0X777777FF)))
		return (false);
	if (!create_audio_options_p2(env, audio, box, num_of_buttons)
		|| !create_ambient_options(env, &audio->ambient, box, num_of_buttons)
		|| !create_gui_options(env, &audio->gui, box, num_of_buttons)
		|| !create_objects_options(env, &audio->objects, box, num_of_buttons)
		|| !container_add(env->gui.settings_menu.container, audio->container))
		return (destroy_audio_options(audio) && 0);
	audio->container->component.is_visible = false;
	return (true);
}

bool		init_audio_options(void *param)
{
	t_env	*env;

	env = param;
	if (env->gui.settings_menu.current_option != AUDIO_OPTION)
	{
		env->gui.settings_menu.audio_button->component.background = 0X777777FF;
		env->gui.settings_menu.audio_button->component.need_redraw = true;
		disable_current_option(&env->gui.settings_menu);
	}
	env->gui.settings_menu.current_option = AUDIO_OPTION;
	env->gui.settings_menu.audio.container->component.is_visible = true;
	return (true);
}
