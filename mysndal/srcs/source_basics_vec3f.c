/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_basics_vec3f.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 02:34:51 by thboura           #+#    #+#             */
/*   Updated: 2020/03/31 17:11:20 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysndal.h"

bool	set_source_position(ALuint source, t_vec3f position)
{
	alSource3f(source, AL_POSITION, position.x, position.y, position.z);
	if (!verify_error())
		return (false);
	return (true);
}

bool	set_source_velocity(ALuint source, t_vec3f velocity)
{
	alSource3f(source, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
	if (!verify_error())
		return (false);
	return (true);
}

bool	get_source_vec3f(ALuint source, ALenum param, t_vec3f *dst)
{
	if (dst == NULL || !(param == AL_POSITION || param == AL_VELOCITY))
		return (false);
	alGetSource3f(source, param, &dst->x, &dst->y, &dst->z);
	if (!verify_error())
		return (false);
	return (true);
}
