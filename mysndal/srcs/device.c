/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   device.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 13:07:55 by thboura           #+#    #+#             */
/*   Updated: 2020/03/09 19:54:01 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysndal.h"

void		show_devices(void)
{
	const ALCchar	*device_list;

	device_list = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
	if (device_list == NULL)
	{
		write(1, "No devices available.\n", 22);
		return ;
	}
	write(1, "Devices:\n", 9);
	while (ft_strlen(device_list) > 0)
	{
		ft_printf("%*s\n", (int)ft_strlen(device_list), device_list);
		device_list += ft_strlen(device_list) + 1;
	}
}

ALCdevice	*get_context_device(ALCcontext *context)
{
	if (context == NULL)
		return (NULL);
	return (alcGetContextsDevice(context));
}

bool		destroy_device(ALCdevice *device)
{
	return (alcCloseDevice(device));
}

ALCdevice	*init_device(char *device_name)
{
	ALCdevice	*ret;

	ret = alcOpenDevice(device_name);
	return (ret);
}
