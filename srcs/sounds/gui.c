/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:44:37 by thboura           #+#    #+#             */
/*   Updated: 2020/06/06 18:44:38 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	destroy_gui(t_gui_sounds *audio_gui)
{
	if (audio_gui->open_pause_menu.available)
		if (!delete_audio(&audio_gui->open_pause_menu))
			return (false);
	if (audio_gui->close_pause_menu.available)
		if (!delete_audio(&audio_gui->close_pause_menu))
			return (false);
	if (audio_gui->select_button.available)
		if (!delete_audio(&audio_gui->select_button))
			return (false);
	return (true);
}

bool	create_open_pause_menu(t_sound_manager *manager,
	t_audio_output *open_pause_menu)
{
	size_t	open_id;

	open_id = add_sound_to_library(manager->master,
		"assets/open_pause_menu.wav", AL_FORMAT_STEREO16);
	if (open_id == (size_t)-1 || open_id != OPEN_PAUSE)
		return (false);
	if (!create_audio(open_pause_menu, manager, open_id))
		return (false);
	if (!(attach_buffer_to_source(&open_pause_menu->source,
		manager->master->library->sounds_list->elem[open_id].data)))
		return (false);
	open_pause_menu->amplitude = 1.f;
	open_pause_menu->available = true;
	return (true);
}

bool	create_close_pause_menu(t_sound_manager *manager,
	t_audio_output *close_pause_menu)
{
	size_t	close_id;

	close_id = add_sound_to_library(manager->master,
		"assets/close_pause_menu.wav", AL_FORMAT_STEREO16);
	if (close_id == (size_t)-1 || close_id != CLOSE_PAUSE)
		return (false);
	if (!create_audio(close_pause_menu, manager, close_id))
		return (false);
	if (!(attach_buffer_to_source(&close_pause_menu->source,
		manager->master->library->sounds_list->elem[close_id].data)))
		return (false);
	close_pause_menu->amplitude = 1.f;
	close_pause_menu->available = true;
	return (true);
}

bool	create_select_button(t_sound_manager *manager,
	t_audio_output *select_button)
{
	size_t	select_id;

	select_id = add_sound_to_library(manager->master, "assets/select.wav",
		AL_FORMAT_STEREO16);
	if (select_id == (size_t)-1 || select_id != SELECT_BUTTON)
		return (false);
	if (!create_audio(select_button, manager, select_id))
		return (false);
	if (!(attach_buffer_to_source(&select_button->source,
		manager->master->library->sounds_list->elem[select_id].data)))
		return (false);
	select_button->amplitude = 1.f;
	select_button->available = true;
	return (true);
}

bool	init_gui(t_sound_manager *manager, t_gui_sounds *audio_gui)
{
	audio_gui->amplitude = 1.f;
	if (!create_open_pause_menu(manager, &audio_gui->open_pause_menu))
		return (destroy_gui(audio_gui));
	if (!create_close_pause_menu(manager, &audio_gui->close_pause_menu))
		return (destroy_gui(audio_gui));
	if (!create_select_button(manager, &audio_gui->select_button))
		return (destroy_gui(audio_gui));
	return (true);
}
