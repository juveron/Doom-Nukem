/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_options_p7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 23:11:23 by thboura           #+#    #+#             */
/*   Updated: 2020/06/24 23:12:37 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	slider_update_end_of_level_amplitude(void *value, void *manager)
{
	return (update_audio_source_amplitude((t_sound_manager *)manager,
		&((t_sound_manager *)manager)->audio_objects.end_of_level,
		((t_sound_manager *)manager)->audio_objects.amplitude,
		*(float *)value));
}
