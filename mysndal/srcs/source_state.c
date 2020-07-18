/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 02:42:25 by thboura           #+#    #+#             */
/*   Updated: 2020/03/16 02:58:23 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysndal.h"

bool	change_source_state(ALuint source, t_source_state state)
{
	if (state == SRC_REWIND)
		alSourceRewind(source);
	else if (state == SRC_PLAY)
		alSourcePlay(source);
	else if (state == SRC_PAUSE)
		alSourcePause(source);
	else if (state == SRC_STOP)
		alSourceStop(source);
	else
		return (false);
	if (!verify_error())
		return (false);
	return (true);
}

bool	change_sources_state(ALuint *sources, ALsizei num_of_sources,
	t_source_state state)
{
	if (num_of_sources <= 0)
		return (false);
	if (state == SRC_REWIND)
		alSourceRewindv(num_of_sources, sources);
	else if (state == SRC_PLAY)
		alSourcePlayv(num_of_sources, sources);
	else if (state == SRC_PAUSE)
		alSourcePausev(num_of_sources, sources);
	else if (state == SRC_STOP)
		alSourceStopv(num_of_sources, sources);
	else
		return (false);
	if (!verify_error())
		return (false);
	return (true);
}
