/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:12:36 by thboura           #+#    #+#             */
/*   Updated: 2020/03/31 17:38:18 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysndal.h"

bool	attach_buffer_to_source(ALuint *source, ALuint *buffer)
{
	if (source == NULL || buffer == NULL)
		return (false);
	alSourcei(*source, AL_BUFFER, *buffer);
	if (!verify_error())
		return (false);
	return (true);
}

bool	destroy_sources(ALuint *sources, size_t num_of_sources, bool need_free)
{
	alDeleteSources(num_of_sources, sources);
	if (need_free)
		free(sources);
	if (!verify_error())
		return (false);
	return (true);
}

ALuint	*init_sources(size_t num_of_sources)
{
	ALuint	*sources;

	if (num_of_sources == 0)
		return (NULL);
	if (!(sources = (ALuint *)malloc(sizeof(ALuint) * num_of_sources)))
		return (NULL);
	alGenSources(num_of_sources, sources);
	if (!verify_error())
	{
		alDeleteSources(num_of_sources, sources);
		free(sources);
		return (NULL);
	}
	return (sources);
}
