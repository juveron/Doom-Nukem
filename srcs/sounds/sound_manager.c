/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 17:03:18 by thboura           #+#    #+#             */
/*   Updated: 2020/06/20 01:44:40 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		destroy_sound_manager(t_sound_manager *manager)
{
	int	ret;

	ret = 0;
	if (!manager->available)
		return (true);
	manager->available = false;
	ret += !destroy_ambient(&manager->audio_ambient);
	ret += !destroy_gui(&manager->audio_gui);
	ret += !destroy_objects(&manager->audio_objects);
	if (manager->master)
		ret += !destroy_default_master(manager->master);
	return (ret == 0);
}

bool		init_sound_manager(t_sound_manager *manager)
{
	manager->available = true;
	if (!(manager->master = init_default_master()))
	{
		ft_dprintf(2, "Sound_master initialization failed.\n");
		return (false);
	}
	if (!set_distance_model(AL_LINEAR_DISTANCE))
		return (destroy_sound_manager(manager));
	if (!init_objects(manager, &manager->audio_objects))
		return (destroy_sound_manager(manager));
	if (!init_gui(manager, &manager->audio_gui))
		return (destroy_sound_manager(manager));
	if (!init_ambient(manager, &manager->audio_ambient))
		return (destroy_sound_manager(manager));
	manager->global_amplitude = 0.3f;
	return (true);
}
