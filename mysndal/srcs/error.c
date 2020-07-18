/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 17:11:28 by thboura           #+#    #+#             */
/*   Updated: 2020/03/06 11:12:04 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysndal.h"

ALenum	catch_error(void)
{
	ALenum	error;

	error = alGetError();
	return (error);
}

bool	verify_error(void)
{
	ALenum	error;

	error = alGetError();
	if (error != AL_NO_ERROR)
		return (false);
	else
		return (true);
}
