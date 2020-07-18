/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:44:26 by thboura           #+#    #+#             */
/*   Updated: 2020/06/06 18:44:27 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	delete_audio(t_audio_output *audio)
{
	return (destroy_sources(&audio->source, 1, false));
}

bool	update_audio_source_amplitude(t_sound_manager *manager,
	t_audio_output *audio, float class_amplitude, float new_amplitude)
{
	float	tmp;

	if (!manager || !audio || class_amplitude > 1.f || class_amplitude < 0.f
		|| new_amplitude > 1.f || new_amplitude < 0.f)
		return (false);
	audio->amplitude = new_amplitude;
	tmp = audio->amplitude * class_amplitude * manager->global_amplitude;
	if (tmp > 1.f || tmp < 0.f)
		return (false);
	return (set_source_amplitude(audio->source, tmp));
}

bool	create_audio(t_audio_output *audio, t_sound_manager *manager,
	size_t buffer_id)
{
	ALuint	*tmp_buffer;

	if (audio->available == true || !manager->master
		|| buffer_id >= NUM_OF_SOURCES)
		return (false);
	if (!(tmp_buffer = init_sources(1)))
		return (false);
	if (!attach_buffer_to_source(tmp_buffer,
		manager->master->library->sounds_list->elem[buffer_id].data))
		return (false);
	audio->amplitude = 1.f;
	audio->source = tmp_buffer[0];
	free(tmp_buffer);
	return (true);
}
