/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_basics_float.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 02:45:43 by thboura           #+#    #+#             */
/*   Updated: 2020/05/30 16:10:52 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysndal.h"

bool	set_source_beginning(ALuint source, float seconds)
{
	alSourcef(source, AL_SEC_OFFSET, seconds);
	if (!verify_error())
		return (false);
	return (true);
}

bool	set_source_amplitude(ALuint source, float gain)
{
	alSourcef(source, AL_GAIN, gain);
	if (!verify_error())
		return (false);
	return (true);
}

bool	set_source_rollof(ALuint source, float gain)
{
	alSourcef(source, AL_ROLLOFF_FACTOR, gain);
	if (!verify_error())
		return (false);
	return (true);
}

bool	set_source_ref_dist(ALuint source, float gain)
{
	alSourcef(source, AL_REFERENCE_DISTANCE, gain);
	if (!verify_error())
		return (false);
	return (true);
}

bool	set_source_max_dist(ALuint source, float gain)
{
	alSourcef(source, AL_MAX_DISTANCE, gain);
	if (!verify_error())
		return (false);
	return (true);
}
