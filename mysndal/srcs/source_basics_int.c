/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_basics_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 17:29:52 by thboura           #+#    #+#             */
/*   Updated: 2020/03/31 17:52:31 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysndal.h"

bool	set_source_relative(ALuint source, int rel)
{
	alSourcei(source, AL_SOURCE_RELATIVE, rel);
	if (!verify_error())
		return (false);
	return (true);
}

bool	set_source_loop(ALuint source, int loop)
{
	alSourcei(source, AL_LOOPING, loop);
	if (!verify_error())
		return (false);
	return (true);
}
