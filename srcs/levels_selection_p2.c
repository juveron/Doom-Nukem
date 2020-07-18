/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_selection_p2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:18:13 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/04 16:54:26 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	update_levels_selection_func(void *param)
{
	t_gui_levels_selection	*levels_selection;
	t_vec2i					pos;
	t_vec2i					mouse_pos;
	t_u64					tmp;

	levels_selection = param;
	pos = get_component_pos(&levels_selection->component);
	mouse_pos = get_mouse_position();
	if (get_button_down(SDL_BUTTON_LEFT, NULL) && is_in_box(mouse_pos,
		&((SDL_Rect){pos.x, pos.y, levels_selection->component.rect.w,
		levels_selection->component.rect.h})))
	{
		tmp = (mouse_pos.y - pos.y) / 30 + levels_selection->start;
		if (tmp < levels_selection->levels->total
			&& tmp != levels_selection->selected_index)
		{
			levels_selection->component.need_redraw = true;
			levels_selection->selected_index = tmp;
			trigger_gui_custom_event(levels_selection->on_selection_change,
				*(t_doom_map **)vector_get(levels_selection->levels,
				levels_selection->selected_index));
		}
	}
	return (true);
}

bool	destroy_levels_selection(
	t_gui_levels_selection **levels_selection)
{
	if (*levels_selection == NULL)
		return (true);
	destroy_component(&(*levels_selection)->component);
	destroy_event_handler((*levels_selection)->on_selection_change);
	free(*levels_selection);
	*levels_selection = NULL;
	return (true);
}
