/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:21:08 by thboura           #+#    #+#             */
/*   Updated: 2020/03/16 18:17:12 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysndal.h"

bool				destroy_default_master(t_default_master *master)
{
	bool	error;

	error = false;
	if (master->library)
		if (!(destroy_sound_player(master->library)))
			error = true;
	if (master->context)
		if (!(destroy_context(master->context)))
			error = true;
	if (master->device)
		if (!(destroy_device(master->device)))
			error = true;
	free(master);
	return (!error);
}

t_default_master	*init_default_master(void)
{
	t_default_master	*ret;

	if (!(ret = (t_default_master *)ft_memalloc(sizeof(t_default_master))))
		return (NULL);
	if (!(ret->device = init_device(NULL)))
	{
		destroy_default_master(ret);
		return (NULL);
	}
	if (!(ret->context = init_audio_context(ret->device)))
	{
		destroy_default_master(ret);
		return (NULL);
	}
	if (!(ret->library = init_sound_player()))
	{
		destroy_default_master(ret);
		return (NULL);
	}
	return (ret);
}

static size_t		buffer_part(t_default_master *master, t_sound_file *sound)
{
	size_t	id;

	if ((id = create_player_buffer(master->library)) == (size_t)-1)
	{
		delete_sound(sound);
		return ((size_t)-1);
	}
	if (!(add_sound_to_buffer(master->library->sounds_list->elem[id].data,
		sound)))
	{
		delete_sound(sound);
		return ((size_t)-1);
	}
	delete_sound(sound);
	return (id);
}

size_t				add_sound_to_library(t_default_master *master,
	char *file_name, ALenum format)
{
	t_sound_file	*sound;

	if (!ft_strcmp(file_name, "") || file_name == NULL)
		return ((size_t)-1);
	if (!(sound = load_sound(file_name)))
		return ((size_t)-1);
	if (sound->format != AL_FORMAT_MONO16 && format == AL_FORMAT_MONO16)
	{
		if (!change_sound_to_mono(sound))
		{
			delete_sound(sound);
			return ((size_t)-1);
		}
	}
	else if (sound->format != AL_FORMAT_STEREO16
		&& format == AL_FORMAT_STEREO16)
	{
		if (!change_sound_to_stereo(sound))
		{
			delete_sound(sound);
			return ((size_t)-1);
		}
	}
	return (buffer_part(master, sound));
}
