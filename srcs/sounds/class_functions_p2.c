/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_functions_p2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:44:29 by thboura           #+#    #+#             */
/*   Updated: 2020/06/24 23:15:50 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	update_ambient_amplitude(t_sound_manager *manager,
	t_ambient_sounds *ambient, float new_amplitude)
{
	if (new_amplitude > 1.f || new_amplitude < 0.f)
		return (false);
	ambient->amplitude = new_amplitude;
	if (!update_audio_source_amplitude(manager, &ambient->ambient_music,
		ambient->amplitude, ambient->ambient_music.amplitude))
		return (false);
	if (!update_audio_source_amplitude(manager, &ambient->game_over_music,
		ambient->amplitude, ambient->game_over_music.amplitude))
		return (false);
	return (true);
}

bool	update_gui_amplitude(t_sound_manager *manager,
	t_gui_sounds *gui, float new_amplitude)
{
	if (new_amplitude > 1.f || new_amplitude < 0.f)
		return (false);
	gui->amplitude = new_amplitude;
	if (!update_audio_source_amplitude(manager, &gui->open_pause_menu,
		gui->amplitude, gui->open_pause_menu.amplitude))
		return (false);
	if (!update_audio_source_amplitude(manager, &gui->close_pause_menu,
		gui->amplitude, gui->close_pause_menu.amplitude))
		return (false);
	if (!update_audio_source_amplitude(manager, &gui->select_button,
		gui->amplitude, gui->select_button.amplitude))
		return (false);
	return (true);
}

bool	update_objects_amplitude(t_sound_manager *manager,
	t_objects_sounds *objects, float new_amplitude)
{
	if (new_amplitude > 1.f || new_amplitude < 0.f)
		return (false);
	objects->amplitude = new_amplitude;
	if (!update_audio_source_amplitude(manager, &objects->start_of_level,
		objects->amplitude, objects->start_of_level.amplitude))
		return (false);
	if (!update_audio_source_amplitude(manager, &objects->end_of_level,
		objects->amplitude, objects->end_of_level.amplitude))
		return (false);
	return (true);
}

bool	update_global_amplitude(t_sound_manager *manager,
	float new_amplitude)
{
	if (new_amplitude > 1.f || new_amplitude < 0.f)
		return (false);
	manager->global_amplitude = new_amplitude;
	if (!update_objects_amplitude(manager, &manager->audio_objects,
		manager->audio_objects.amplitude))
		return (false);
	if (!update_gui_amplitude(manager, &manager->audio_gui,
		manager->audio_gui.amplitude))
		return (false);
	if (!update_ambient_amplitude(manager, &manager->audio_ambient,
		manager->audio_ambient.amplitude))
		return (false);
	return (true);
}
