/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 14:18:43 by thboura           #+#    #+#             */
/*   Updated: 2020/03/16 02:16:57 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysndal.h"

void				delete_sound(t_sound_file *sound)
{
	if (sound->samples)
		free(sound->samples);
	free(sound);
}

static t_sound_file	*delete_return(t_sound_file *sound, SNDFILE *file)
{
	delete_sound(sound);
	sf_close(file);
	return (NULL);
}

static void			set_sound_infos(t_sound_file *sound, SF_INFO file_infos)
{
	sound->nb_samples = (ALsizei)(file_infos.channels * file_infos.frames);
	sound->sample_rate = (ALsizei)(file_infos.samplerate);
	sound->channels = (ALsizei)(file_infos.channels);
	sound->frames = (ALsizei)(file_infos.frames);
}

t_sound_file		*load_sound(char *file_name)
{
	t_sound_file	*sound;
	SF_INFO			file_infos;
	SNDFILE			*file;

	if (!(sound = (t_sound_file *)ft_memalloc(sizeof(t_sound_file))))
		return (NULL);
	file = sf_open(file_name, SFM_READ, &file_infos);
	if (!file)
		return (delete_return(sound, file));
	set_sound_infos(sound, file_infos);
	if (!(sound->samples = (ALshort *)malloc(sizeof(ALshort) * sound->
		nb_samples)))
		return (delete_return(sound, file));
	if (sf_read_short(file, sound->samples, sound->nb_samples) < sound->
		nb_samples)
		return (delete_return(sound, file));
	if (file_infos.channels == 1)
		sound->format = AL_FORMAT_MONO16;
	else if (file_infos.channels == 2)
		sound->format = AL_FORMAT_STEREO16;
	else
		return (delete_return(sound, file));
	sf_close(file);
	return (sound);
}
