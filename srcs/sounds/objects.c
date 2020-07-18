/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:44:41 by thboura           #+#    #+#             */
/*   Updated: 2020/06/06 18:44:41 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	destroy_objects(t_objects_sounds *audio_objects)
{
	if (audio_objects->start_of_level.available)
		if (!delete_audio(&audio_objects->start_of_level))
			return (false);
	if (audio_objects->end_of_level.available)
		if (!delete_audio(&audio_objects->end_of_level))
			return (false);
	return (true);
}

bool	create_start_of_level(t_sound_manager *manager,
	t_audio_output *start_of_level)
{
	size_t	start_id;

	start_id = add_sound_to_library(manager->master,
		"assets/UI_sound.wav", AL_FORMAT_MONO16);
	if (start_id == (size_t)-1 || start_id != START_OF_LEVEL)
		return (false);
	if (!create_audio(start_of_level, manager, start_id))
		return (false);
	if (!set_source_rollof(start_of_level->source, 1.f))
		return (false);
	if (!set_source_ref_dist(start_of_level->source, 2.f))
		return (false);
	if (!set_source_max_dist(start_of_level->source, 10.f))
		return (false);
	if (!set_source_loop(start_of_level->source, true))
		return (false);
	if (!(attach_buffer_to_source(&start_of_level->source,
		manager->master->library->sounds_list->elem[start_id].data)))
		return (false);
	start_of_level->amplitude = 1.f;
	start_of_level->available = true;
	return (true);
}

bool	create_end_of_level(t_sound_manager *manager,
	t_audio_output *end_of_level)
{
	size_t	end_id;

	end_id = add_sound_to_library(manager->master,
		"assets/UI_sound1.wav", AL_FORMAT_MONO16);
	if (end_id == (size_t)-1 || end_id != END_OF_LEVEL)
		return (false);
	if (!create_audio(end_of_level, manager, end_id))
		return (false);
	if (!set_source_rollof(end_of_level->source, 1.f))
		return (false);
	if (!set_source_ref_dist(end_of_level->source, 2.f))
		return (false);
	if (!set_source_max_dist(end_of_level->source, 10.f))
		return (false);
	if (!set_source_loop(end_of_level->source, true))
		return (false);
	if (!(attach_buffer_to_source(&end_of_level->source,
		manager->master->library->sounds_list->elem[end_id].data)))
		return (false);
	end_of_level->amplitude = 1.f;
	end_of_level->available = true;
	return (true);
}

bool	init_objects(t_sound_manager *manager, t_objects_sounds *audio_objects)
{
	audio_objects->amplitude = 1.f;
	if (!create_start_of_level(manager, &audio_objects->start_of_level))
		return (false);
	if (!create_end_of_level(manager, &audio_objects->end_of_level))
		return (false);
	return (true);
}
