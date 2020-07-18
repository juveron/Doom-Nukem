/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_sound.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 02:17:17 by thboura           #+#    #+#             */
/*   Updated: 2020/03/16 19:43:26 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysndal.h"

static bool	end_of_mono(t_sound_file *sound)
{
	sound->channels = 1;
	sound->nb_samples = sound->frames;
	sound->format = AL_FORMAT_MONO16;
	return (true);
}

bool		change_sound_to_mono(t_sound_file *sound)
{
	ALshort		*ret;
	ALsizei		i;
	ALsizei		j;
	ALfloat		tmpf;

	i = 0;
	if (!(ret = (ALshort *)malloc(sizeof(ALshort) * sound->frames)))
		return (false);
	while (i < sound->frames)
	{
		tmpf = 0;
		j = 0;
		while (j < sound->channels)
		{
			tmpf += sound->samples[i * sound->channels + j];
			j++;
		}
		tmpf /= sound->channels;
		ret[i++] = (ALshort)tmpf;
	}
	free(sound->samples);
	sound->samples = ret;
	return (end_of_mono(sound));
}

static bool	end_of_stereo(t_sound_file *sound)
{
	sound->channels = 2;
	sound->nb_samples = sound->frames * sound->channels;
	sound->format = AL_FORMAT_STEREO16;
	return (true);
}

bool		change_sound_to_stereo(t_sound_file *sound)
{
	ALshort		*ret;
	ALsizei		i;
	ALsizei		j;
	ALfloat		tmpf;

	i = 0;
	if (!(ret = (ALshort *)malloc(sizeof(ALshort) * (sound->frames * 2))))
		return (false);
	while (i < sound->frames)
	{
		tmpf = sound->samples[i];
		j = 0;
		while (j < 2)
		{
			ret[i * 2 + j] = (ALshort)tmpf;
			j++;
		}
		i++;
	}
	free(sound->samples);
	sound->samples = ret;
	return (end_of_stereo(sound));
}
