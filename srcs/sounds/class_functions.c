/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:44:32 by thboura           #+#    #+#             */
/*   Updated: 2020/06/24 23:16:45 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	change_ambient_sources_state(t_ambient_sounds *ambient,
	t_source_state state)
{
	if (!change_source_state(ambient->ambient_music.source, state))
		return (false);
	if (!change_source_state(ambient->game_over_music.source, state))
		return (false);
	return (true);
}

bool	change_gui_sources_state(t_gui_sounds *gui,
	t_source_state state)
{
	if (!change_source_state(gui->open_pause_menu.source, state))
		return (false);
	if (!change_source_state(gui->close_pause_menu.source, state))
		return (false);
	if (!change_source_state(gui->select_button.source, state))
		return (false);
	return (true);
}

bool	change_objects_sources_state(t_objects_sounds *objects,
	t_source_state state)
{
	if (!change_source_state(objects->start_of_level.source, state))
		return (false);
	if (!change_source_state(objects->end_of_level.source, state))
		return (false);
	return (true);
}

bool	change_all_sources_state(t_sound_manager *manager,
	t_source_state state)
{
	if (!change_objects_sources_state(&manager->audio_objects, state))
		return (false);
	if (!change_gui_sources_state(&manager->audio_gui, state))
		return (false);
	if (!change_ambient_sources_state(&manager->audio_ambient, state))
		return (false);
	return (true);
}
