/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_options_p2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:33:09 by thboura           #+#    #+#             */
/*   Updated: 2020/07/12 02:58:44 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		destroy_ambient_options(t_ambient_options *ambient)
{
	int	ret;

	ret = 0;
	if (!ambient)
		return (false);
	ret += !destroy_fslider(&ambient->game_over_music_amplitude_fslider);
	ret += !destroy_label(&ambient->game_over_music_amplitude_label);
	ret += !destroy_fslider(&ambient->ambient_music_amplitude_fslider);
	ret += !destroy_label(&ambient->ambient_music_amplitude_label);
	ret += !destroy_fslider(&ambient->ambient_amplitude_fslider);
	ret += !destroy_label(&ambient->ambient_amplitude_label);
	return (ret == 0);
}

static bool	create_ambient_options_p3(t_env *env, t_ambient_options *ambient,
	SDL_Rect box, size_t num_of_buttons)
{
	if (!(ambient->game_over_music_amplitude_label = create_label(vec2i(75,
			3 * (box.h / num_of_buttons) + (box.h / num_of_buttons / 2
			- (int)(19 / 2)) + (box.h % num_of_buttons)), 0xFFFFFFFF,
			env->fonts.deja_vu_sans_momo_16, 0x666666FF))
		|| !label_change_name(ambient->game_over_music_amplitude_label,
			"Game_over_music")
		|| !container_add(env->gui.settings_menu.audio.container,
			ambient->game_over_music_amplitude_label)
		|| !(ambient->game_over_music_amplitude_fslider = create_fslider(
			(SDL_Rect){box.w / 2, 3 * (box.h / num_of_buttons) + box.h
			/ num_of_buttons / 4 + (box.h % num_of_buttons),
			box.w / 2 - 25, box.h / num_of_buttons / 2}, 0.f, 1.f))
		|| !add_custom_action(ambient->game_over_music_amplitude_fslider->
			on_value_change,
			&(t_custom_event){&slider_update_game_over_music_amplitude,
			&env->sound_manager}))
		return (destroy_ambient_options(ambient));
	fslider_set_percent_value(ambient->game_over_music_amplitude_fslider,
		env->sound_manager.audio_ambient.game_over_music.amplitude);
	if (!container_add(env->gui.settings_menu.audio.container,
		ambient->game_over_music_amplitude_fslider))
		return (destroy_ambient_options(ambient));
	return (true);
}

static bool	create_ambient_options_p2(t_env *env, t_ambient_options *ambient,
	SDL_Rect box, size_t num_of_buttons)
{
	if (!(ambient->ambient_music_amplitude_label = create_label(vec2i(75,
			2 * (box.h / num_of_buttons) + (box.h / num_of_buttons / 2
			- (int)(19 / 2)) + (box.h % num_of_buttons)), 0xFFFFFFFF,
			env->fonts.deja_vu_sans_momo_16, 0x666666FF))
		|| !label_change_name(ambient->ambient_music_amplitude_label,
			"Ambient_music")
		|| !container_add(env->gui.settings_menu.audio.container,
			ambient->ambient_music_amplitude_label)
		|| !(ambient->ambient_music_amplitude_fslider = create_fslider(
			(SDL_Rect){box.w / 2, 2 * (box.h / num_of_buttons) + box.h
			/ num_of_buttons / 4 + (box.h % num_of_buttons),
			box.w / 2 - 25, box.h / num_of_buttons / 2}, 0.f, 1.f))
		|| !add_custom_action(ambient->ambient_music_amplitude_fslider->
			on_value_change,
			&(t_custom_event){&slider_update_ambient_music_amplitude,
			&env->sound_manager}))
		return (destroy_ambient_options(ambient));
	fslider_set_percent_value(ambient->ambient_music_amplitude_fslider,
		env->sound_manager.audio_ambient.ambient_music.amplitude);
	if (!container_add(env->gui.settings_menu.audio.container,
		ambient->ambient_music_amplitude_fslider))
		return (destroy_ambient_options(ambient));
	return (create_ambient_options_p3(env, ambient, box, num_of_buttons));
}

bool		create_ambient_options(t_env *env, t_ambient_options *ambient,
	SDL_Rect box, size_t num_of_buttons)
{
	if (!(ambient->ambient_amplitude_label = create_label(vec2i(50,
			1 * (box.h / num_of_buttons) + (box.h / num_of_buttons / 2
			- (int)(19 / 2)) + (box.h % num_of_buttons)), 0xFFFFFFFF,
			env->fonts.deja_vu_sans_momo_16, 0x666666FF))
		|| !label_change_name(ambient->ambient_amplitude_label, "Ambient")
		|| !container_add(env->gui.settings_menu.audio.container,
			ambient->ambient_amplitude_label)
		|| !(ambient->ambient_amplitude_fslider = create_fslider(
			(SDL_Rect){box.w / 2, 1 * (box.h / num_of_buttons) + box.h
			/ num_of_buttons / 4 + (box.h % num_of_buttons),
			box.w / 2 - 25, box.h / num_of_buttons / 2}, 0.f, 1.f))
		|| !add_custom_action(ambient->ambient_amplitude_fslider->
			on_value_change, &(t_custom_event){&slider_update_ambient_amplitude,
			&env->sound_manager}))
		return (destroy_ambient_options(ambient));
	fslider_set_percent_value(ambient->ambient_amplitude_fslider,
		env->sound_manager.audio_ambient.amplitude);
	if (!container_add(env->gui.settings_menu.audio.container,
		ambient->ambient_amplitude_fslider))
		return (destroy_ambient_options(ambient));
	return (create_ambient_options_p2(env, ambient, box, num_of_buttons));
}
