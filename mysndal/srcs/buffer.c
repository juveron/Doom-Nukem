/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:50:39 by thboura           #+#    #+#             */
/*   Updated: 2020/06/24 23:28:50 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysndal.h"

int		get_buffer_length_in_samples(ALuint *buffer)
{
	ALint	size;
	ALint	channels;
	ALint	bits;
	float	ret;

	alGetBufferi(*buffer, AL_SIZE, &size);
	alGetBufferi(*buffer, AL_CHANNELS, &channels);
	alGetBufferi(*buffer, AL_BITS, &bits);
	ret = size * 8 / (channels * bits);
	if (!verify_error())
		return (-1);
	return (ret);
}

float	get_buffer_duration_in_seconds(ALuint *buffer)
{
	ALint	frequency;
	float	ret;

	alGetBufferi(*buffer, AL_FREQUENCY, &frequency);
	ret = (float)get_buffer_length_in_samples(buffer) / (float)frequency;
	if (!verify_error())
		return (-1);
	return (ret);
}

bool	add_sound_to_buffer(ALuint *buffer, t_sound_file *sound)
{
	if (buffer == NULL || sound == NULL || sound->samples == NULL)
		return (false);
	alBufferData(*buffer, sound->format, sound->samples,
		sound->nb_samples * sizeof(ALushort), sound->sample_rate);
	if (!verify_error())
		return (false);
	return (true);
}

bool	destroy_buffers(ALuint *buffers, size_t num_of_buffers, bool need_free)
{
	alDeleteBuffers(num_of_buffers, buffers);
	if (need_free)
		free(buffers);
	if (!verify_error())
		return (false);
	return (true);
}

ALuint	*init_buffers(size_t num_of_buffers)
{
	ALuint	*buffers;

	if (num_of_buffers == 0)
		return (NULL);
	if (!(buffers = (ALuint *)malloc(sizeof(ALuint) * num_of_buffers)))
		return (NULL);
	alGenBuffers(num_of_buffers, buffers);
	if (!verify_error())
	{
		alDeleteBuffers(num_of_buffers, buffers);
		free(buffers);
		return (NULL);
	}
	return (buffers);
}
