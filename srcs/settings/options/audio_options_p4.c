/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_options_p4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:33:18 by thboura           #+#    #+#             */
/*   Updated: 2020/06/24 23:49:48 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		destroy_objects_options(t_objects_options *objects)
{
	int	ret;

	ret = 0;
	if (!objects)
		return (true);
	ret += !destroy_fslider(&objects->end_of_level_amplitude_fslider);
	ret += !destroy_label(&objects->end_of_level_amplitude_label);
	ret += !destroy_fslider(&objects->start_of_level_amplitude_fslider);
	ret += !destroy_label(&objects->start_of_level_amplitude_label);
	ret += !destroy_fslider(&objects->objects_amplitude_fslider);
	ret += !destroy_label(&objects->objects_amplitude_label);
	return (ret == 0);
}

static bool	create_objects_options_p3(t_env *env, t_objects_options *objects,
	SDL_Rect box, size_t num_of_buttons)
{
	if (!(objects->end_of_level_amplitude_label = create_label(vec2i(75,
			10 * (box.h / num_of_buttons) + (box.h / num_of_buttons / 2
			- (int)(19 / 2)) + (box.h % num_of_buttons)), 0xFFFFFFFF,
			env->fonts.deja_vu_sans_momo_16, 0x666666FF))
		|| !label_change_name(objects->end_of_level_amplitude_label,
			"End_of_level")
		|| !container_add(env->gui.settings_menu.audio.container,
			objects->end_of_level_amplitude_label)
		|| !(objects->end_of_level_amplitude_fslider = create_fslider(
			(SDL_Rect){box.w / 2, 10 * (box.h / num_of_buttons) + box.h
			/ num_of_buttons / 4 + (box.h % num_of_buttons), box.w / 2 - 25,
			box.h / num_of_buttons / 2}, 0.f, 1.f))
		|| !add_custom_action(objects->end_of_level_amplitude_fslider->
			on_value_change,
			&(t_custom_event){&slider_update_end_of_level_amplitude,
			&env->sound_manager}))
		return (destroy_objects_options(objects) && 0);
	fslider_set_percent_value(objects->end_of_level_amplitude_fslider,
		env->sound_manager.audio_objects.end_of_level.amplitude);
	if (!container_add(env->gui.settings_menu.audio.container,
		objects->end_of_level_amplitude_fslider))
		return (destroy_objects_options(objects) && 0);
	return (true);
}

static bool	create_objects_options_p2(t_env *env, t_objects_options *objects,
	SDL_Rect box, size_t num_of_buttons)
{
	if (!(objects->start_of_level_amplitude_label = create_label(vec2i(75,
		9 * (box.h / num_of_buttons) + (box.h / num_of_buttons / 2
		- (int)(19 / 2)) + (box.h % num_of_buttons)), 0xFFFFFFFF,
		env->fonts.deja_vu_sans_momo_16, 0x666666FF))
		|| !label_change_name(objects->start_of_level_amplitude_label,
		"Start_of_level")
		|| !container_add(env->gui.settings_menu.audio.container,
		objects->start_of_level_amplitude_label)
		|| !(objects->start_of_level_amplitude_fslider = create_fslider(
		(SDL_Rect){box.w / 2, 9 * (box.h / num_of_buttons) + box.h
		/ num_of_buttons / 4 + (box.h % num_of_buttons), box.w / 2 - 25,
		box.h / num_of_buttons / 2}, 0.f, 1.f))
		|| !add_custom_action(objects->start_of_level_amplitude_fslider->
			on_value_change,
			&(t_custom_event){&slider_update_start_of_level_amplitude,
			&env->sound_manager}))
		return (destroy_objects_options(objects) && 0);
	fslider_set_percent_value(objects->start_of_level_amplitude_fslider,
		env->sound_manager.audio_objects.start_of_level.amplitude);
	if (!container_add(env->gui.settings_menu.audio.container,
		objects->start_of_level_amplitude_fslider))
		return (destroy_objects_options(objects) && 0);
	return (create_objects_options_p3(env, objects, box,
		num_of_buttons));
}

bool		create_objects_options(t_env *env, t_objects_options *objects,
	SDL_Rect box, size_t num_of_buttons)
{
	if (!(objects->objects_amplitude_label = create_label(vec2i(50,
			8 * (box.h / num_of_buttons) + (box.h / num_of_buttons / 2
			- (int)(19 / 2)) + (box.h % num_of_buttons)), 0xFFFFFFFF,
			env->fonts.deja_vu_sans_momo_16, 0x666666FF))
		|| !label_change_name(objects->objects_amplitude_label, "Objects")
		|| !container_add(env->gui.settings_menu.audio.container,
			objects->objects_amplitude_label)
		|| !(objects->objects_amplitude_fslider = create_fslider(
			(SDL_Rect){box.w / 2, 8 * (box.h / num_of_buttons) + box.h
			/ num_of_buttons / 4 + (box.h % num_of_buttons), box.w / 2 - 25,
			box.h / num_of_buttons / 2}, 0.f, 1.f))
		|| !add_custom_action(objects->objects_amplitude_fslider->
			on_value_change, &(t_custom_event){&slider_update_objects_amplitude,
			&env->sound_manager}))
		return (destroy_objects_options(objects) && 0);
	fslider_set_percent_value(objects->objects_amplitude_fslider,
		env->sound_manager.audio_objects.amplitude);
	if (!container_add(env->gui.settings_menu.audio.container,
		objects->objects_amplitude_fslider))
		return (destroy_objects_options(objects) && 0);
	return (create_objects_options_p2(env, objects, box,
		num_of_buttons));
}
