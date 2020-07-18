/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listener.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:38:30 by thboura           #+#    #+#             */
/*   Updated: 2020/03/31 17:15:43 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysndal.h"

bool	set_listener_position(t_vec3f position)
{
	alListener3f(AL_POSITION, position.x, position.y, position.z);
	if (!verify_error())
		return (false);
	return (true);
}

bool	set_listener_velocity(t_vec3f velocity)
{
	alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
	if (!verify_error())
		return (false);
	return (true);
}

bool	set_listener_orientation(t_vec3f forward, t_vec3f up)
{
	ALfloat		*orientation;

	orientation = (ALfloat[6]){forward.x, forward.y, forward.z,
		up.x, up.y, up.z};
	alListenerfv(AL_ORIENTATION, orientation);
	if (!verify_error())
		return (false);
	return (true);
}

bool	get_listener_vec3f(ALenum param, t_vec3f *src)
{
	if (src == NULL || !(param == AL_POSITION || param == AL_VELOCITY))
		return (false);
	alGetListener3f(param, &src->x, &src->y, &src->z);
	if (!verify_error())
		return (false);
	return (true);
}
