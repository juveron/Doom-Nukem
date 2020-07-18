/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_options_p6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:34:20 by thboura           #+#    #+#             */
/*   Updated: 2020/06/24 23:12:32 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	slider_update_game_over_music_amplitude(void *value, void *manager)
{
	return (update_audio_source_amplitude((t_sound_manager *)manager,
		&((t_sound_manager *)manager)->audio_ambient.game_over_music,
		((t_sound_manager *)manager)->audio_ambient.amplitude,
		*(float *)value));
}

bool	slider_update_open_pause_amplitude(void *value, void *manager)
{
	return (update_audio_source_amplitude((t_sound_manager *)manager,
		&((t_sound_manager *)manager)->audio_gui.open_pause_menu,
		((t_sound_manager *)manager)->audio_gui.amplitude,
		*(float *)value));
}

bool	slider_update_close_pause_amplitude(void *value, void *manager)
{
	return (update_audio_source_amplitude((t_sound_manager *)manager,
		&((t_sound_manager *)manager)->audio_gui.close_pause_menu,
		((t_sound_manager *)manager)->audio_gui.amplitude,
		*(float *)value));
}

bool	slider_update_select_button_amplitude(void *value, void *manager)
{
	return (update_audio_source_amplitude((t_sound_manager *)manager,
		&((t_sound_manager *)manager)->audio_gui.select_button,
		((t_sound_manager *)manager)->audio_gui.amplitude,
		*(float *)value));
}

bool	slider_update_start_of_level_amplitude(void *value, void *manager)
{
	return (update_audio_source_amplitude((t_sound_manager *)manager,
		&((t_sound_manager *)manager)->audio_objects.start_of_level,
		((t_sound_manager *)manager)->audio_objects.amplitude,
		*(float *)value));
}
