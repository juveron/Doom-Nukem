/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_options_p5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:34:14 by thboura           #+#    #+#             */
/*   Updated: 2020/06/06 18:34:14 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	slider_update_global_amplitude(void *value, void *manager)
{
	return (update_global_amplitude((t_sound_manager *)manager,
		*(float *)value));
}

bool	slider_update_ambient_amplitude(void *value, void *manager)
{
	return (update_ambient_amplitude((t_sound_manager *)manager,
		&((t_sound_manager *)manager)->audio_ambient, *(float *)value));
}

bool	slider_update_gui_amplitude(void *value, void *manager)
{
	return (update_gui_amplitude((t_sound_manager *)manager,
		&((t_sound_manager *)manager)->audio_gui, *(float *)value));
}

bool	slider_update_objects_amplitude(void *value, void *manager)
{
	return (update_objects_amplitude((t_sound_manager *)manager,
		&((t_sound_manager *)manager)->audio_objects, *(float *)value));
}

bool	slider_update_ambient_music_amplitude(void *value, void *manager)
{
	return (update_audio_source_amplitude((t_sound_manager *)manager,
		&((t_sound_manager *)manager)->audio_ambient.ambient_music,
		((t_sound_manager *)manager)->audio_ambient.amplitude,
		*(float *)value));
}
