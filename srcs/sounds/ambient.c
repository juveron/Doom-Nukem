/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:44:16 by thboura           #+#    #+#             */
/*   Updated: 2020/06/24 23:03:35 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	destroy_ambient(t_ambient_sounds *audio_ambient)
{
	if (audio_ambient->ambient_music.available)
		if (!delete_audio(&audio_ambient->ambient_music))
			return (false);
	if (audio_ambient->game_over_music.available)
		if (!delete_audio(&audio_ambient->game_over_music))
			return (false);
	return (true);
}

bool	create_ambient_music(t_sound_manager *manager,
	t_audio_output *ambient_music)
{
	size_t	ambient_id;

	ambient_id = add_sound_to_library(manager->master, "assets/Mii_Theme.wav",
		AL_FORMAT_STEREO16);
	if (ambient_id == (size_t)-1 || ambient_id != AMBIENT_MUSIC)
		return (false);
	if (!create_audio(ambient_music, manager, ambient_id))
		return (false);
	if (!set_source_loop(ambient_music->source, true))
		return (false);
	if (!(attach_buffer_to_source(&ambient_music->source,
		manager->master->library->sounds_list->elem[ambient_id].data)))
		return (false);
	ambient_music->amplitude = 1.f;
	ambient_music->available = true;
	return (true);
}

bool	create_game_over_music(t_sound_manager *manager,
	t_audio_output *game_over_music)
{
	size_t	game_over_id;

	game_over_id = add_sound_to_library(manager->master, "assets/Death.wav",
		AL_FORMAT_STEREO16);
	if (game_over_id == (size_t)-1 || game_over_id != GAME_OVER_MUSIC)
		return (false);
	if (!create_audio(game_over_music, manager, game_over_id))
		return (false);
	if (!(attach_buffer_to_source(&game_over_music->source,
		manager->master->library->sounds_list->elem[game_over_id].data)))
		return (false);
	game_over_music->amplitude = 1.f;
	game_over_music->available = true;
	return (true);
}

bool	init_ambient(t_sound_manager *manager, t_ambient_sounds *audio_ambient)
{
	audio_ambient->amplitude = 1.f;
	if (!create_ambient_music(manager, &audio_ambient->ambient_music))
		return (false);
	if (!create_game_over_music(manager, &audio_ambient->game_over_music))
		return (false);
	return (true);
}
