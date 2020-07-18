/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 17:23:47 by thboura           #+#    #+#             */
/*   Updated: 2020/03/09 19:50:32 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysndal.h"

bool			destroy_sound_player(t_sound_player *player)
{
	bool	error;
	size_t	i;

	error = false;
	i = 0;
	while (i < player->sounds_list->total)
	{
		if (!destroy_buffers(player->sounds_list->elem[i].data, 1, false))
			error = true;
		i++;
	}
	map_free(player->sounds_list);
	free(player);
	return (!error);
}

t_sound_player	*init_sound_player(void)
{
	t_sound_player	*ret;

	if (!(ret = (t_sound_player *)ft_memalloc(sizeof(t_sound_player))))
		return (NULL);
	if (!(ret->sounds_list = map_init(sizeof(ALuint))))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

size_t			create_player_buffer(t_sound_player *player)
{
	ALuint	buffer;

	alGenBuffers(1, &buffer);
	if (!verify_error())
		return ((size_t)-1);
	if (!map_add(player->sounds_list, player->unique_id, &buffer))
		return ((size_t)-1);
	player->unique_id++;
	return (player->unique_id - 1);
}

size_t			add_buffers_to_player(t_sound_player *player, ALuint *buffers,
	size_t num_of_buffers)
{
	size_t	i;

	i = 0;
	while (i < num_of_buffers)
	{
		if (!map_add(player->sounds_list, player->unique_id, &buffers[i++]))
			return ((size_t)-1);
		player->unique_id++;
	}
	return (player->unique_id - 1);
}
