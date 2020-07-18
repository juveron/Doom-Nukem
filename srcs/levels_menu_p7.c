/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_menu_p7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 11:18:58 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/13 11:18:59 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "levels_menu_internal.h"

static void	move_index(t_levels_menu *level_menu, size_t size)
{
	if (*level_menu->levels_selection->current_map_index == size - 1
		|| level_menu->levels_selection->selected_index
			< *level_menu->levels_selection->current_map_index)
		(*level_menu->levels_selection->current_map_index)--;
	if (level_menu->levels_selection->selected_index == size - 1)
		level_menu->levels_selection->selected_index--;
}

static bool	delete_levels(void *param)
{
	t_levels_menu	*level_menu;
	t_doom_map		*map;
	size_t			size;
	bool			current;

	level_menu = param;
	current = false;
	size = level_menu->levels_selection->levels->total;
	if (size == 1)
		return (true);
	if (*level_menu->levels_selection->current_map_index
		== level_menu->levels_selection->selected_index)
		current = true;
	map = *(t_doom_map **)vector_get(level_menu->levels_selection->levels,
			level_menu->levels_selection->selected_index);
	vector_delete(level_menu->levels_selection->levels,
			level_menu->levels_selection->selected_index);
	free_map(map);
	move_index(level_menu, size);
	level_menu->levels_selection->component.need_redraw = true;
	if (current)
		load_levels(level_menu);
	return (true);
}

bool		create_delete_level_button(t_levels_menu *levels_menu, t_env *env)
{
	if (!(levels_menu->delete_map_button = create_button((SDL_Rect){335, 550,
			110, 30}, 0x777777FF, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_level_menu(levels_menu));
	button_change_name(levels_menu->delete_map_button, "Delete map");
	if (!add_default_action(levels_menu->delete_map_button->
			on_click, &(t_default_event){&delete_levels, levels_menu}))
		return (destroy_level_menu(levels_menu));
	if (!container_add(levels_menu->container, levels_menu->delete_map_button))
		return (destroy_level_menu(levels_menu));
	return (true);
}
