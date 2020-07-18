/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:11:10 by thboura           #+#    #+#             */
/*   Updated: 2020/03/15 16:03:02 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysndal.h"

bool			destroy_context(ALCcontext *context)
{
	ALCdevice	*device;
	ALCenum		error;

	if (!context)
		return (false);
	if ((device = get_context_device(context)) == NULL)
		return (false);
	alcDestroyContext(context);
	error = alcGetError(device);
	if (error != ALC_NO_ERROR)
		return (false);
	return (true);
}

bool			destroy_current_context(void)
{
	ALCcontext	*context;

	context = alcGetCurrentContext();
	alcMakeContextCurrent(NULL);
	if (!(destroy_context(context)))
		return (false);
	return (true);
}

ALCcontext		*init_audio_context(ALCdevice *device)
{
	ALCcontext	*ret;
	ALCenum		error;

	if (!device)
		return (NULL);
	ret = alcCreateContext(device, NULL);
	error = alcGetError(device);
	if (error != ALC_NO_ERROR)
		return (NULL);
	alcMakeContextCurrent(ret);
	return (ret);
}
